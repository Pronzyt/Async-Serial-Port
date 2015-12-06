#ifndef ASYNCPORT_H
#define ASYNCPORT_H

#include <string>
#include <functional>
#include "Options.h"
#include "Exceptions.h"


class AsyncPort{
public:
	typedef std::function<void(void)> ok_callback;
	typedef std::function<void(port_error)> error_callback;

	AsyncPort();
	~AsyncPort();

	port_error open(const std::string& name);
	port_error close();
	void write(void const* write_buf, size_t size, ok_callback ok_func, error_callback error_func);
	void read(void* read_buf, size_t size, ok_callback ok_func, error_callback error_func);

	port_error set_stop_bits(const stop_bits& sb);
	port_error get_stop_bits(stop_bits& sb);

	port_error set_parity(const parity& par);
	port_error get_parity(parity& par);

	port_error set_flow_control(const flow_control& fc);
	port_error get_flow_control(flow_control& fc);

	port_error set_baud_rate(const baud_rate& br);
	port_error get_baud_rate(baud_rate& br);

	unsigned int get_timeout() const;
	void set_timeout(unsigned int value);

private:
	/*noncopyable!*/
	AsyncPort(const AsyncPort&) = delete;
	AsyncPort& operator=(const AsyncPort&) = delete;

	/*pointer to implementation*/
	class AsyncPortImpl;
	AsyncPortImpl* pimpl;
};

#endif
