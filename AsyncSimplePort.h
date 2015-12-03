#ifndef ASYNCSIMPLEPORT_H
#define ASYNCSIMPLEPORT_H

//#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <functional>
#include <cstdint>
#include <algorithm>
#include "boost\asio.hpp"
#include "boost\bind.hpp"
#include "boost\timer.hpp"
#include "boost\thread.hpp"
#include "boost\detail\endian.hpp"
#include "boost\icl\discrete_interval.hpp"
#include <boost\core\noncopyable.hpp>

#include "Options.h"
#include "Options.ipp"

const boost::posix_time::seconds TIMEOUT(5);


//class port_error{
//public:
//	port_error() = delete;
//	port_error(const boost::system::error_code& error) : m_msg(error.message()){};
//	std::string message(){return m_msg;};
//private:
//	std::string m_msg;
//};


class AsyncPortImpl : boost::noncopyable {
	using serial_port = boost::asio::serial_port;
	using io_service = boost::asio::io_service;
	using deadline_timer = boost::asio::deadline_timer;
public:
	using error_code = boost::system::error_code;
	typedef std::function<void(void)> ok_callback;
	typedef std::function<void(error_code)> error_callback;

	AsyncPortImpl();	
	~AsyncPortImpl();
	
	error_code open(const std::string& name);
	error_code close();
	void write(void const* write_buf, size_t size, ok_callback ok_func, error_callback error_func);
	void read(void* read_buf, size_t size, ok_callback ok_func, error_callback error_func);

	template<typename Ty>
	error_code set_option(Ty option)
	{
		error_code error;
		get_impl<Ty>::impl temp(static_cast<get_impl<Ty>::impl::type>(option.value()));
		m_port.set_option(temp, error);
		return error;
	};


private:
	void read_handler(deadline_timer& timer, ok_callback ok_func, error_callback error_func, const boost::system::error_code& error, std::size_t bytes_transferred);
	void write_handler(ok_callback ok_func, error_callback error_func, const boost::system::error_code& error, std::size_t bytes_transferred);
	void wait_handler(serial_port& ser_port, const boost::system::error_code& error);

	io_service m_io_service;
	serial_port m_port;
	std::auto_ptr<io_service::work> m_work;
	boost::thread m_thread;
	deadline_timer m_timer;
};

#endif
