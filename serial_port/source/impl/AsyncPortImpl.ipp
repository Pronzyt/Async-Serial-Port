#ifndef ASYNCPORTIMPL_IPP
#define ASYNCPORTIMPL_IPP

//#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <functional>
#include <cstdint>
#include <algorithm>
#include <thread>
#include "boost\asio.hpp"
#include "boost\bind.hpp"
#include "boost\timer.hpp"
#include "boost\thread.hpp"
#include "boost\detail\endian.hpp"
#include "boost\icl\discrete_interval.hpp"
#include <boost\core\noncopyable.hpp>

const unsigned int default_timeout = 5;

class AsyncPort::AsyncPortImpl : boost::noncopyable {
	using serial_port = boost::asio::serial_port;
	using io_service = boost::asio::io_service;
	using deadline_timer = boost::asio::deadline_timer;
	using seconds = boost::posix_time::seconds;
	using streambuf = boost::asio::streambuf;
public:
	using error_code = boost::system::error_code;
	typedef std::function<void(size_t)> ok_callback;
	typedef std::function<void(error_code, size_t)> error_callback;

	AsyncPortImpl();	
	~AsyncPortImpl();
	
	error_code open(const std::string& name);
	error_code close();

	void write(void const* write_buf, size_t size, ok_callback ok_func, error_callback error_func);
	void read(void* read_buf, size_t size, ok_callback ok_func, error_callback error_func);
	void read_until(void* read_buf, size_t size, std::string delim, ok_callback ok_func, error_callback error_func);
	void read_some(void* read_buf, size_t size, ok_callback ok_func, error_callback error_func);

	template<typename Ty>
	error_code set_option(const Ty& option)
	{
		error_code error;
		m_port.set_option(option.get_impl(), error);
		return error;
	};

	template<typename Ty>
	error_code get_option(Ty& option)
	{
		error_code error;
		m_port.get_option(option.get_impl(), error);
		return error;
	};

	/*!!!*/
	unsigned int get_timeout() const
	{
		return m_timeout.total_seconds();
	};

	void set_timeout(unsigned int value)
	{
		m_timeout = seconds(value);
	};

private:
	void read_handler(deadline_timer& timer, ok_callback ok_func, error_callback error_func, const error_code& error, size_t bytes_transferred);
	void write_handler(ok_callback ok_func, error_callback error_func, const error_code& error, std::size_t bytes_transferred);
	void wait_handler(serial_port& ser_port, const error_code& error);

	io_service m_io_service;
	serial_port m_port;
	std::auto_ptr<io_service::work> m_work;
	boost::thread m_thread;
	deadline_timer m_timer;
	seconds m_timeout;
};


AsyncPort::AsyncPortImpl::AsyncPortImpl()
	:m_port(m_io_service), m_work(new io_service::work(m_io_service)), m_timer(m_io_service), m_timeout(default_timeout)
{
	m_thread = boost::thread(boost::bind(&boost::asio::io_service::run, &m_io_service));
};


AsyncPort::AsyncPortImpl::error_code AsyncPort::AsyncPortImpl::open(const std::string& name)
{
	boost::system::error_code error_code;
	return m_port.open(name, error_code);
};


AsyncPort::AsyncPortImpl::error_code AsyncPort::AsyncPortImpl::close()
{
	boost::system::error_code error_code;
	return m_port.close(error_code);
};


AsyncPort::AsyncPortImpl::~AsyncPortImpl()
{
	m_port.close();
	m_work.reset();
	m_thread.join();
};


void AsyncPort::AsyncPortImpl::read_handler(deadline_timer& timer, ok_callback ok_func, error_callback error_func, const error_code& error, size_t bytes_transferred)
{
	if (error)
	{
		// No data was read!
		error_func(error, bytes_transferred);
		return;
	};
	ok_func(bytes_transferred);
	timer.cancel();  // will cause wait_callback to fire with an error
};


void AsyncPort::AsyncPortImpl::write_handler(ok_callback ok_func, error_callback error_func, const error_code& error, size_t bytes_transferred)
{
	if (error)
	{
		error_func(error, bytes_transferred);
		return;
	};
	ok_func(bytes_transferred);
};


void AsyncPort::AsyncPortImpl::wait_handler(serial_port& ser_port, const boost::system::error_code& error)
{
	if (error)
	{
		// Data was read and this timeout was canceled
		return;
	};
	if (ser_port.is_open())
		ser_port.cancel();  // will cause read_callback to fire with an error
};


void AsyncPort::AsyncPortImpl::read(void* read_buf, size_t size, ok_callback ok_func, error_callback error_func)
{
	m_timer.expires_from_now(m_timeout);
	m_timer.async_wait(boost::bind(&AsyncPortImpl::wait_handler, this,
		boost::ref(m_port),
		boost::asio::placeholders::error));
	
	boost::asio::async_read(m_port,
		boost::asio::buffer(read_buf, size),
		boost::bind(&AsyncPortImpl::read_handler, this,
		boost::ref(m_timer),
		ok_func,
		error_func,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
};


void AsyncPort::AsyncPortImpl::read_some(void* read_buf, size_t size, ok_callback ok_func, error_callback error_func)
{
	m_timer.expires_from_now(m_timeout);
	m_timer.async_wait(boost::bind(&AsyncPortImpl::wait_handler, this,
		boost::ref(m_port),
		boost::asio::placeholders::error));

	m_port.async_read_some(boost::asio::buffer(read_buf, size),
			boost::bind(&AsyncPortImpl::read_handler, this,
				boost::ref(m_timer),
				ok_func,
				error_func,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
};



void AsyncPort::AsyncPortImpl::read_until(void* read_buf, size_t size, std::string delim, ok_callback ok_func, error_callback error_func)
{
	m_timer.expires_from_now(m_timeout);
	m_timer.async_wait(boost::bind(&AsyncPortImpl::wait_handler, this,
		boost::ref(m_port),
		boost::asio::placeholders::error));

	boost::asio::streambuf read_buffer(size);
	boost::asio::async_read_until(m_port,
		read_buffer,
		delim,
		boost::bind(&AsyncPortImpl::read_handler, this,
			boost::ref(m_timer),
			ok_func,
			error_func,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
};


void AsyncPort::AsyncPortImpl::write(void const* write_buf, size_t size, ok_callback ok_func, error_callback error_func)
{
	boost::asio::async_write(m_port,
		boost::asio::buffer(write_buf, size),
		boost::bind(&AsyncPortImpl::write_handler, this,
		ok_func,
		error_func,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred)
		);
};


#endif
