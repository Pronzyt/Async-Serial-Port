#ifndef SYNCSIMPLEPORT_H
#define SYNCSIMPLEPORT_H

#include <functional>
#include <cstdint>
#include <algorithm>
#include "boost\asio.hpp"
#include "boost\bind.hpp"
#include "boost\timer.hpp"
#include "boost\thread.hpp"
#include "boost\detail\endian.hpp"
#include "boost\icl\discrete_interval.hpp"


class SyncSimplePort : public boost::noncopyable{
public:
	
	SyncSimplePort() = delete;

	explicit SyncSimplePort(const char* name);

	~SyncSimplePort();

	void write(void* const write_buf, size_t size);
	void read(void* read_buf, size_t size);
private:
	using io_service = boost::asio::io_service;
	using serial_port = boost::asio::serial_port;
	using deadline_timer = boost::asio::deadline_timer;

	size_t completion_condition(bool stop, const boost::system::error_code& error, std::size_t bytes_transferred, size_t size);
	void wait_handler(bool& stop, serial_port& ser_port, const boost::system::error_code& error);


	deadline_timer m_timer;
};






#endif
