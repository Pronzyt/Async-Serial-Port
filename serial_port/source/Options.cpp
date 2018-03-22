#include "options/Options.h"
#include "impl/Options.ipp"


/*Stop bits*/

stop_bits::stop_bits(type t)
	:pimpl(new stop_bits_impl(static_cast<stop_bits_impl::type>(t)))
{};


stop_bits::~stop_bits()
{
	delete pimpl;
};


/*Parity*/

parity::parity(type t)
	:pimpl(new parity_impl(static_cast<parity_impl::type>(t)))
{};


parity::~parity()
{
	delete pimpl;
};


/*Flow control*/

flow_control::flow_control(type t)
	:pimpl(new flow_control_impl(static_cast<flow_control_impl::type>(t)))
{};


flow_control::~flow_control()
{
	delete pimpl;
};

/*Baud rate*/

baud_rate::baud_rate(unsigned int rate)
	:pimpl(new baud_rate_impl(rate))
{};


baud_rate::~baud_rate()
{
	delete pimpl;
};

/*Character size*/

character_size::character_size(unsigned int size)
	:pimpl(new character_size_impl(size))
{};


character_size::~character_size()
{
	delete pimpl;
};
