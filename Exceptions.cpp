#include "Exceptions.h"
#include "Exceptions.ipp"


template<>
port_error::port_error(const error_code& error) 
	: m_msg(error.message()){};