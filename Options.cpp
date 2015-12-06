#include "Options.h"
#include "Options.ipp"

/*Stop bits*/

stop_bits::stop_bits(type t)
	:pimpl(new stop_bits_impl(static_cast<stop_bits_impl::type>(t)))
{};


stop_bits::stop_bits_impl& stop_bits::get_impl()
{
	return *pimpl;
};


const stop_bits::stop_bits_impl& stop_bits::get_impl() const
{
	return *pimpl;
}


stop_bits::~stop_bits()
{
	delete pimpl;
};


/*Parity*/

parity::parity(type t)
	:pimpl(new parity_impl(static_cast<parity_impl::type>(t)))
{};


parity::parity_impl& parity::get_impl()
{
	return *pimpl;
};


const parity::parity_impl& parity::get_impl() const
{
	return *pimpl;
}


parity::~parity()
{
	delete pimpl;
};


/*Flow control*/

flow_control::flow_control(type t)
	:pimpl(new flow_control_impl(static_cast<flow_control_impl::type>(t)))
{};


flow_control::flow_control_impl& flow_control::get_impl()
{
	return *pimpl;
};


const flow_control::flow_control_impl& flow_control::get_impl() const
{
	return *pimpl;
}


flow_control::~flow_control()
{
	delete pimpl;
};

/*Baud rate*/

baud_rate::baud_rate(unsigned int rate)
	:pimpl(new baud_rate_impl(rate))
{};


baud_rate::baud_rate_impl& baud_rate::get_impl()
{
	return *pimpl;
};


const baud_rate::baud_rate_impl& baud_rate::get_impl() const
{
	return *pimpl;
}


baud_rate::~baud_rate()
{
	delete pimpl;
};

