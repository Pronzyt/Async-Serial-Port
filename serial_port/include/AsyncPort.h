#ifndef ASYNCPORT_H
#define ASYNCPORT_H

#ifdef SERIAL_PORT_DLL_EXPORTS
#define SERIAL_PORT_DLL_API  __declspec(dllexport) 
#else
#define SERIAL_PORT_DLL_API  __declspec(dllimport) 
#endif


#include <functional>
#include "options/Options.h"
#include "exception/Exceptions.h"


class AsyncPort{
public:
	typedef std::function<void(AsyncPort*, size_t)> ok_callback;
	typedef std::function<void(AsyncPort*, port_error, size_t)> error_callback;

	SERIAL_PORT_DLL_API AsyncPort();
	SERIAL_PORT_DLL_API ~AsyncPort();

	SERIAL_PORT_DLL_API void open(const std::string& name, port_error& error);
	SERIAL_PORT_DLL_API void close(port_error& error);
	
	SERIAL_PORT_DLL_API void write(void const* write_buf, size_t size, ok_callback ok_func, error_callback error_func);
	SERIAL_PORT_DLL_API void read(void* read_buf, size_t size, ok_callback ok_func, error_callback error_func);
	SERIAL_PORT_DLL_API void read_some(void* read_buf, size_t size, ok_callback ok_func, error_callback error_func);

	SERIAL_PORT_DLL_API void set_stop_bits(const stop_bits& sb, port_error& error);
	SERIAL_PORT_DLL_API void get_stop_bits(stop_bits& sb, port_error& error);

	SERIAL_PORT_DLL_API void set_parity(const parity& par, port_error& error);
	SERIAL_PORT_DLL_API void get_parity(parity& par, port_error& error);

	SERIAL_PORT_DLL_API void set_flow_control(const flow_control& fc, port_error& error);
	SERIAL_PORT_DLL_API void get_flow_control(flow_control& fc, port_error& error);

	SERIAL_PORT_DLL_API void set_baud_rate(const baud_rate& br, port_error& error);
	SERIAL_PORT_DLL_API void get_baud_rate(baud_rate& br, port_error& error);

	SERIAL_PORT_DLL_API void set_character_size(const character_size& br, port_error& error);
	SERIAL_PORT_DLL_API void get_character_size(character_size& br, port_error& error);

	SERIAL_PORT_DLL_API void get_timeout(unsigned int& value) const;
	SERIAL_PORT_DLL_API void set_timeout(const unsigned int& value);

private:
	/*noncopyable!*/
	AsyncPort(const AsyncPort&) = delete;
	AsyncPort& operator=(const AsyncPort&) = delete;

	/*pointer to implementation*/
	class AsyncPortImpl;
	AsyncPortImpl* pimpl;
};

#endif
