#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

#ifdef SERIAL_PORT_DLL_EXPORTS
#define SERIAL_PORT_DLL_API __declspec(dllexport) 
#else
#define SERIAL_PORT_DLL_API __declspec(dllimport) 
#endif

class port_error{
public:
	SERIAL_PORT_DLL_API port_error() {};
	SERIAL_PORT_DLL_API std::string message() const;

	template<typename Ty>
	SERIAL_PORT_DLL_API port_error(const Ty& error);
	SERIAL_PORT_DLL_API explicit operator bool() const;
private:
	//port_error() = delete;
	std::string m_msg;
	bool m_error;
};

#endif