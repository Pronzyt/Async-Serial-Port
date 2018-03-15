#include "exception\Exceptions.h"
#include "impl\Exceptions.ipp"



template<>
port_error::port_error(const error_code& error) 
	: m_msg(error.message()), m_error(error.value()){};

std::string port_error::message() const
{
	return m_msg;
};


port_error::operator bool() const
{
	return m_error;
};
