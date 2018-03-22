#ifndef OPTIONS_IPP
#define OPTIONS_IPP

#include "boost\asio.hpp"


class stop_bits::stop_bits_impl : public boost::asio::serial_port::stop_bits{
public:
	explicit stop_bits_impl(stop_bits_impl::type t)
			:boost::asio::serial_port::stop_bits(t)
		{};
	~stop_bits_impl(){};
};


class parity::parity_impl : public boost::asio::serial_port::parity{
public:
	explicit parity_impl(parity_impl::type t)
		:boost::asio::serial_port::parity(t)
	{};
	~parity_impl(){};
};


class flow_control::flow_control_impl : public boost::asio::serial_port::flow_control{
public:
	explicit flow_control_impl(flow_control_impl::type t)
		:boost::asio::serial_port::flow_control(t)
	{};
	~flow_control_impl(){};
};


class baud_rate::baud_rate_impl : public boost::asio::serial_port::baud_rate{
public:
	explicit baud_rate_impl(unsigned int rate = 0)
	: boost::asio::serial_port::baud_rate(rate)
	{};
	~baud_rate_impl(){};
};


class character_size::character_size_impl : public boost::asio::serial_port::character_size {
public:
	explicit character_size_impl(unsigned int size = 0)
		: boost::asio::serial_port::character_size(size)
	{};
	~character_size_impl() {};
};

#endif






