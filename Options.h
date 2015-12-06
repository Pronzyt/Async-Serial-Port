#ifndef OPTIONS_H
#define OPTIONS_H

class stop_bits{
	class stop_bits_impl;
public:
	enum type { one, onepointfive, two };
	explicit stop_bits(type t = one);
	type value();
	~stop_bits();

	stop_bits_impl& get_impl();
	const stop_bits_impl& get_impl() const;
private:
	stop_bits_impl* pimpl;
};


class parity{
	class parity_impl;
public:
	enum type { none, odd, even };
	explicit parity(type t = none);
	type value() const;
	~parity();

	parity_impl& get_impl();
	const parity_impl& get_impl() const;
private:
	parity_impl* pimpl;
};


class flow_control{
	class flow_control_impl;
public:
	enum type { none, software, hardware };
	explicit flow_control(type t = none);
	type value() const;
	~flow_control();

	flow_control_impl& get_impl();
	const flow_control_impl& get_impl() const;
private:
	flow_control_impl* pimpl;
};


class baud_rate{
	class baud_rate_impl;
public:
	explicit baud_rate(unsigned int rate = 0);
	unsigned int value() const;
	~baud_rate();

	baud_rate_impl& get_impl();
	const baud_rate_impl& get_impl() const;
private:
	baud_rate_impl* pimpl;
};

#endif
