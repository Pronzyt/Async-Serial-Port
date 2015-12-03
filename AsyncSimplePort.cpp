#include "AsyncSimplePort.h"


AsyncPortImpl::AsyncPortImpl()
	:m_port(m_io_service), m_work(new io_service::work(m_io_service)), m_timer(m_io_service)
{
	//m_port.set_option(serial_port::baud_rate(115200)); //baud_rate
	//m_port.set_option(serial_port::stop_bits(serial_port::stop_bits::one)); // stop_bit
	//m_port.set_option(serial_port::flow_control(serial_port::flow_control::none)); // flow_control
	//m_port.set_option(serial_port::parity(serial_port::parity::none)); // parity
	//serial_port::parity parity;
	//m_port.get_option(parity);
	//m_port.set_option(serial_port::character_size(8));
	m_thread = boost::thread(boost::bind(&boost::asio::io_service::run, &m_io_service));
};


AsyncPortImpl::error_code AsyncPortImpl::open(const std::string& name)
{
	boost::system::error_code error_code;
	return m_port.open(name, error_code);
};


AsyncPortImpl::error_code AsyncPortImpl::close()
{
	boost::system::error_code error_code;
	return m_port.close(error_code);
};


AsyncPortImpl::~AsyncPortImpl()
{
	m_port.close();
	m_work.reset();	
	m_thread.join();
};


void AsyncPortImpl::read_handler(deadline_timer& timer, ok_callback ok_func, error_callback error_func, const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (error)
	{
		// No data was read!
		error_func(error);
		return;
	};
	ok_func();
	timer.cancel();  // will cause wait_callback to fire with an error
};


void AsyncPortImpl::write_handler(ok_callback ok_func, error_callback error_func, const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (error)
	{
		error_func(error);
		return;
	};
	ok_func();	
};


void AsyncPortImpl::wait_handler(serial_port& ser_port, const boost::system::error_code& error)
{
	if (error)
	{
		// Data was read and this timeout was canceled
		return;
	};
	if (ser_port.is_open())
		ser_port.cancel();  // will cause read_callback to fire with an error
};


void AsyncPortImpl::read(void* read_buf, size_t size, ok_callback ok_func, error_callback error_func)
{
	//full async read
	m_timer.expires_from_now(TIMEOUT);
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


void AsyncPortImpl::write(void const* write_buf, size_t size, ok_callback ok_func, error_callback error_func)
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
