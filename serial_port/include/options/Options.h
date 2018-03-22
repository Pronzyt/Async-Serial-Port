#ifndef OPTIONS_H
#define OPTIONS_H


#ifdef SERIAL_PORT_DLL_EXPORTS
#define SERIAL_PORT_DLL_API __declspec(dllexport) 
#else
#define SERIAL_PORT_DLL_API __declspec(dllimport) 
#endif


class stop_bits{
	class stop_bits_impl;
public:
	enum type { one, onepointfive, two };
	SERIAL_PORT_DLL_API explicit stop_bits(type t = one);
	SERIAL_PORT_DLL_API type value();
	SERIAL_PORT_DLL_API ~stop_bits();

private:
	stop_bits_impl* pimpl;
	friend class AsyncPort;
};


class parity{
	class parity_impl;
public:
	enum type { none, odd, even };
	SERIAL_PORT_DLL_API explicit parity(type t = none);
	SERIAL_PORT_DLL_API type value() const;
	SERIAL_PORT_DLL_API ~parity();

private:
	parity_impl* pimpl;
	friend class AsyncPort;
};


class flow_control{
	class flow_control_impl;
public:
	enum type { none, software, hardware };
	SERIAL_PORT_DLL_API explicit flow_control(type t = none);
	SERIAL_PORT_DLL_API type value() const;
	SERIAL_PORT_DLL_API ~flow_control();

private:
	flow_control_impl* pimpl;
	friend class AsyncPort;
};


class baud_rate{
	class baud_rate_impl;
public:
	SERIAL_PORT_DLL_API explicit baud_rate(unsigned int rate = 0);
	SERIAL_PORT_DLL_API unsigned int value() const;
	SERIAL_PORT_DLL_API ~baud_rate();

private:
	baud_rate_impl* pimpl;
	friend class AsyncPort;
};


class character_size{
	class character_size_impl;
public:
	SERIAL_PORT_DLL_API explicit character_size(unsigned int size = 0);
	SERIAL_PORT_DLL_API unsigned int value() const;
	SERIAL_PORT_DLL_API ~character_size();

private:
	character_size_impl* pimpl;
	friend class AsyncPort;

};

#endif
