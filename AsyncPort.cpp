#include "AsyncPort.h"
#include "AsyncPortImpl.ipp"
#include "Options.ipp"


AsyncPort::AsyncPort()
	:pimpl(new AsyncPortImpl)
{};


AsyncPort::~AsyncPort()
{
	delete pimpl;
};


port_error AsyncPort::open(const std::string& name)
{
	return pimpl->open(name);
};


port_error AsyncPort::close()
{
	return pimpl->close();
};


void AsyncPort::read(void* read_buf, size_t size, ok_callback ok_func, error_callback error_func)
{
	pimpl->read(read_buf, size, ok_func, error_func);
};


void AsyncPort::write(void const* write_buf, size_t size, ok_callback ok_func, error_callback error_func)
{
	pimpl->write(write_buf, size, ok_func, error_func);
};


port_error AsyncPort::set_stop_bits(const stop_bits& sb)
{
	return pimpl->set_option(sb);
};


port_error AsyncPort::get_stop_bits(stop_bits& sb)
{
	return pimpl->get_option(sb);
};


port_error AsyncPort::set_parity(const parity& par)
{
	return pimpl->set_option(par);
};


port_error AsyncPort::get_parity(parity& par)
{
	return pimpl->get_option(par);
};


port_error AsyncPort::set_flow_control(const flow_control& fc)
{
	return pimpl->set_option(fc);
};


port_error AsyncPort::get_flow_control(flow_control& fc)
{
	return pimpl->get_option(fc);
};


port_error AsyncPort::set_baud_rate(const baud_rate& br)
{
	return pimpl->set_option(br);
};


port_error AsyncPort::get_baud_rate(baud_rate& br)
{
	return pimpl->get_option(br);
};


void AsyncPort::set_timeout(unsigned int value)
{
	return pimpl->set_timeout(value); 
};

