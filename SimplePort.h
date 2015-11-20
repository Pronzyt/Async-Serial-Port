#ifndef SIMPLEPORT_H
#define SIMPLEPORT_H

//#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <functional>
#include <array>
#include <algorithm>
#include "boost\asio.hpp"
#include "boost\bind.hpp"
#include "boost\timer.hpp"
#include "boost\thread.hpp"
#include "boost\detail\endian.hpp"
#include "boost\icl\discrete_interval.hpp"
#include "PhysicalQuantities.h"
#include "Utils.h"


const size_t SENT_MESSAGE_SIZE = 17;
const size_t RECEIVE_MESSAGE_SIZE = 8;
const boost::posix_time::seconds TIMEOUT(5);

//Numeration starts from zero!!!
const size_t FREQ_BYTE_NUM = 9;
const size_t FREQ2_BYTE_NUM = 2;
const size_t A_BYTE_NUM = 6;

const size_t FREQ_SIZE = 4;
const size_t FREQ2_SIZE = 4;


typedef uint8_t message_item;

const size_t HEARTBEAT_MESSAGE_SIZE = 1;
const size_t HEARTBEAT_ANSWER_SIZE = 10;
const std::array<message_item, HEARTBEAT_MESSAGE_SIZE> HEARTBEAT_MESSAGE = { 0xAB };
const std::array<message_item, HEARTBEAT_ANSWER_SIZE> HEARTBEAT_ANSWER = { 'S', 'A', 'P', 'F', 'I', 'R', '1', 'A' };


class SimplePort{
public:
	typedef std::function<void(power_type)>  callback_type;
	SimplePort() = delete;
	SimplePort(const char* name, size_t buffer_size = 10);
	~SimplePort();
	void setFreq(freq_type freq);
	//void setA();
	bool deviceIsAvailable();
	power_type receive(freq_type);

private:
	using io_service = boost::asio::io_service;
	using serial_port = boost::asio::serial_port;
	using deadline_timer = boost::asio::deadline_timer;

	typedef std::array<message_item, SENT_MESSAGE_SIZE> sent_message_type;
	typedef std::array<message_item, RECEIVE_MESSAGE_SIZE> receive_message_type;

	void write(const message_item* read_buf, size_t size);
	bool read(message_item* read_buf, size_t size);

	//void read_handler(deadline_timer& timer, bool& data_available, const boost::system::error_code& error, std::size_t bytes_transferred);
	void write_handler(const boost::system::error_code& error, std::size_t bytes_transferred);
	void wait_handler(serial_port& ser_port, const boost::system::error_code& error);
	void wait_handler(bool& stop, serial_port& ser_port, const boost::system::error_code& error);
	size_t completion_condition(bool stop, const boost::system::error_code& error,std::size_t bytes_transferred);

	io_service m_io_service;
	serial_port m_port;
	deadline_timer m_timer;
	std::auto_ptr<io_service::work> m_work;
	sent_message_type m_sent_message;
	receive_message_type m_receive_message;
	boost::thread m_thread;
};

#endif
