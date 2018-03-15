#include "AsyncPort.h"
#include "impl\AsyncPortImpl.ipp"
#include "impl\Options.ipp"


AsyncPort::AsyncPort()
	:pimpl(new AsyncPortImpl)
{};


AsyncPort::~AsyncPort()
{
	delete pimpl;
};


void AsyncPort::open(const std::string& name, port_error& error)
{
	error = pimpl->open(name);
};


void AsyncPort::close(port_error& error)
{
	error = pimpl->close();
};


void AsyncPort::read(void* read_buf, size_t size, ok_callback ok_func, error_callback error_func)
{
	pimpl->read(read_buf, size, 
		[this, ok_func](){ return ok_func(this); }, 
		[this, error_func](port_error error){return error_func(this, error); });
};


void AsyncPort::write(void const* write_buf, size_t size, ok_callback ok_func, error_callback error_func)
{
	pimpl->write(write_buf, size, 
		[this, ok_func](){ return ok_func(this);}, 
		[this, error_func](port_error error){return error_func(this, error);});
};


void AsyncPort::set_stop_bits(const stop_bits& sb, port_error& error)
{
	error = pimpl->set_option(sb);
};


void AsyncPort::get_stop_bits(stop_bits& sb, port_error& error)
{
	error = pimpl->get_option(sb);
};


void AsyncPort::set_parity(const parity& par, port_error& error)
{
	error = pimpl->set_option(par);
};


void AsyncPort::get_parity(parity& par, port_error& error)
{
	error = pimpl->get_option(par);
};


void AsyncPort::set_flow_control(const flow_control& fc, port_error& error)
{
	error = pimpl->set_option(fc);
};


void AsyncPort::get_flow_control(flow_control& fc, port_error& error)
{
	error = pimpl->get_option(fc);
};


void AsyncPort::set_baud_rate(const baud_rate& br, port_error& error)
{
	error = pimpl->set_option(br);
};


void AsyncPort::get_baud_rate(baud_rate& br, port_error& error)
{
	error = pimpl->get_option(br);
};


void AsyncPort::get_timeout(unsigned int& value) const
{
	value = pimpl->get_timeout();
};

void AsyncPort::set_timeout(const unsigned int& value)
{
	pimpl->set_timeout(value);
};

