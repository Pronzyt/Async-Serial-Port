#include "exception\Exceptions.h"
#include "impl\Exceptions.ipp"



template<>
port_error::port_error(const error_code& error) 
	: m_msg(error.message()){};

std::string port_error::message()
{
	return m_msg;
};
