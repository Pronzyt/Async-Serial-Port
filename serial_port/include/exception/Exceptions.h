#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

#ifdef SERIAL_PORT_DLL_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define SERIAL_PORT_DLL_DLL_API __declspec(dllimport) 
#endif

class port_error{
public:
	DLL_API std::string message();

	template<typename Ty>
	DLL_API port_error(const Ty& error);
	port_error(){};
private:
	//port_error() = delete;
	std::string m_msg;
	int m_value;
};

#endif