#include "SimplePort.h"


SimplePort::SimplePort(const char* name, size_t buffer_size)
	:m_port(m_io_service, name), m_timer(m_io_service), m_work(new io_service::work(m_io_service)), 
	m_sent_message(sent_message_type{ { 0x90, 0x08, 0x0, 0x0, 0x0, 0x0, 0x21, 0x0, 0x02, 0x0, 0x0, 0x0, 0x0, 0x0, 0x08, 0x04, 0x01} }),
	m_receive_message{}
{
	m_port.set_option(serial_port::baud_rate(38400)); //baud_rate
	m_port.set_option(serial_port::stop_bits(serial_port::stop_bits::one)); // stop_bit
	m_port.set_option(serial_port::flow_control(serial_port::flow_control::none)); // flow_control
	m_port.set_option(serial_port::parity(serial_port::parity::none)); // parity
	m_thread = boost::thread(boost::bind(&boost::asio::io_service::run, &m_io_service));
};


SimplePort::~SimplePort()
{
	m_port.close();
	m_work.reset();	
	m_thread.join();
};


void SimplePort::setFreq(freq_type freq)
{
	place(freq, &m_sent_message[FREQ_BYTE_NUM]);
	place_inv(freq_type(freq * unknown_coef), &m_sent_message[FREQ2_BYTE_NUM]);
};


//void SimplePort::read_handler(deadline_timer& timer, bool& data_available, const boost::system::error_code& error, std::size_t bytes_transferred)
//{
//	if (error)
//	{
//		// No data was read!
//		data_available = false;
//		return;
//	};
//
//	timer.cancel();  // will cause wait_callback to fire with an error
//	data_available = true;
//};


void SimplePort::write_handler(
	const boost::system::error_code& error, // Result of operation.
	std::size_t bytes_transferred           // Number of bytes written from the
											// buffers. If an error occurred,
											// this will be less than the sum
											// of the buffer sizes.
	)
{

};


void SimplePort::wait_handler(serial_port& ser_port, const boost::system::error_code& error)
{
	if (error)
	{
		// Data was read and this timeout was canceled
		return;
	};
	//
	ser_port.cancel();  // will cause read_callback to fire with an error
};


void SimplePort::wait_handler(bool& stop, serial_port& ser_port, const boost::system::error_code& error)
{
	if (error)
	{
		// Data was read and this timeout was canceled
		return;
	};

	stop = true;
	//ser_port.cancel();  // will cause read_callback to fire with an error
};


std::size_t SimplePort::completion_condition(
	//if timer was fired
	bool stop,

	// Result of latest read_some operation.
	const boost::system::error_code& error,

	// Number of bytes transferred so far.
	std::size_t bytes_transferred
	)
{
	if (stop || error)
		return 0;
	else
		return (RECEIVE_MESSAGE_SIZE - bytes_transferred);
};


bool SimplePort::read(message_item* read_buf,  size_t size)
{
	//full async read
	//bool data_available = false;
	//boost::asio::async_read(m_port,
	//	boost::asio::buffer(m_receive_message.data(), m_receive_message.size()),
	//	boost::bind(&SimplePort::read_handler, this,
	//		boost::ref(m_timer),
	//		boost::ref(data_available),
	//		boost::asio::placeholders::error,
	//		boost::asio::placeholders::bytes_transferred));
	//m_timer.expires_from_now(TIMEOUT);
	//m_timer.async_wait(boost::bind(&SimplePort::wait_handler, this,
	//				boost::ref(m_port), 
	//				boost::asio::placeholders::error));

	//blocking read with timer
	bool stop = false;
	m_timer.expires_from_now(TIMEOUT);
	m_timer.async_wait(boost::bind(&SimplePort::wait_handler, this,
					boost::ref(stop),
					boost::ref(m_port), 
					boost::asio::placeholders::error));
	boost::asio::read(m_port, 
					boost::asio::buffer(read_buf, size),
					boost::bind(&SimplePort::completion_condition, this,
								boost::ref(stop), 
								boost::asio::placeholders::error,
								boost::asio::placeholders::bytes_transferred));
	bool data_available = !stop;
	if (data_available)
		m_timer.cancel();
	return data_available;
};


void SimplePort::write(const message_item* read_buf, size_t size)
{
	boost::asio::async_write(m_port,
		boost::asio::buffer(m_sent_message.data(), m_sent_message.size()),
		boost::bind(&SimplePort::write_handler, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred)
		);
};


bool SimplePort::deviceIsAvailable()
{
	write(HEARTBEAT_MESSAGE.data(), HEARTBEAT_MESSAGE.size());
	std::array<message_item, HEARTBEAT_ANSWER_SIZE> buffer;
	read(buffer.data(), HEARTBEAT_ANSWER_SIZE);
	return (buffer == HEARTBEAT_ANSWER);	
};


power_type SimplePort::receive(freq_type freq)
{
	setFreq(freq);
	write(m_sent_message.data(), m_sent_message.size());
	read(m_receive_message.data(), m_receive_message.size());
	return getPower(m_receive_message.data());
};


