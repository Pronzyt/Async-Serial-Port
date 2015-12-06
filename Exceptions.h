#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>


class port_error{
public:
	std::string message();

	template<typename Ty>
	port_error(const Ty& error);

private:
	port_error() = delete;
	std::string m_msg;
};

#endif