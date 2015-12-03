#include "SyncSimplePort.h"


////completion condition is used to stop blocking read if timer fires
//std::size_t AsyncSimplePort::completion_condition(bool stop, const boost::system::error_code& error, std::size_t bytes_transferred, size_t size)
//{
//	//if timer has been fired or error stop reading
//	if (stop || error)
//		return 0;
//	//try to read some more
//	return (size - bytes_transferred);
//};




//void AsyncSimplePort::wait_handler(bool& stop, serial_port& ser_port, const boost::system::error_code& error)
//{
//	if (error)
//	{
//		// Data was read and this timeout was canceled
//		return;
//	};
//
//	stop = true;
//	//ser_port.cancel();  // will cause read_callback to fire with an error
//};


//void AsyncSimplePort::read(void* read_buf,  size_t size)
//{
//	//blocking read with timer
//	//bool stop = false;
//	//m_timer.expires_from_now(TIMEOUT);
//	//m_timer.async_wait(boost::bind(&AsyncSimplePort::wait_handler, this,
//	//				boost::ref(stop),
//	//				boost::ref(m_port), 
//	//				boost::asio::placeholders::error));
//	//boost::asio::read(m_port, 
//	//				boost::asio::buffer(read_buf, size),
//	//				boost::bind(&AsyncSimplePort::completion_condition, this,
//	//							boost::ref(stop), 
//	//							boost::asio::placeholders::error,
//	//							boost::asio::placeholders::bytes_transferred,
//	//							boost::ref(size)));
//	//bool data_available = !stop;
//	//if (data_available)
//	//	m_timer.cancel();
//	//return data_available;
//};