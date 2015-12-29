#ifndef OPTIONS_H
#define OPTIONS_H


#ifdef SERIAL_PORT_DLL_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define SERIAL_PORT_DLL_DLL_API __declspec(dllimport) 
#endif


class stop_bits{
	class stop_bits_impl;
public:
	enum type { one, onepointfive, two };
	DLL_API explicit stop_bits(type t = one);
	DLL_API type value();
	DLL_API ~stop_bits();

	DLL_API stop_bits_impl& get_impl();
	DLL_API const stop_bits_impl& get_impl() const;
private:
	stop_bits_impl* pimpl;
};


class parity{
	class parity_impl;
public:
	enum type { none, odd, even };
	DLL_API explicit parity(type t = none);
	DLL_API type value() const;
	DLL_API ~parity();

	DLL_API parity_impl& get_impl();
	DLL_API const parity_impl& get_impl() const;
private:
	parity_impl* pimpl;
};


class flow_control{
	class flow_control_impl;
public:
	enum type { none, software, hardware };
	DLL_API explicit flow_control(type t = none);
	DLL_API type value() const;
	DLL_API ~flow_control();

	DLL_API flow_control_impl& get_impl();
	DLL_API const flow_control_impl& get_impl() const;
private:
	flow_control_impl* pimpl;
};


class baud_rate{
	class baud_rate_impl;
public:
	DLL_API explicit baud_rate(unsigned int rate = 0);
	DLL_API unsigned int value() const;
	DLL_API ~baud_rate();

	DLL_API baud_rate_impl& get_impl();
	DLL_API const baud_rate_impl& get_impl() const;
private:
	baud_rate_impl* pimpl;
};

#endif
