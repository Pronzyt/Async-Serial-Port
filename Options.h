#ifndef OPTIONS_H
#define OPTIONS_H
#include <memory>

//class base_option
//{
//	
//};


class stop_bits
{
public:
	enum type { one, onepointfive, two };
	explicit stop_bits(type t = one) : m_value(t) {};
	type value() const { return m_value; };
private:
	type m_value;
};


//class parity
//{
//public:
//	enum type { none, odd, even };
//	explicit parity(type t = none);
//	type value() const { return m_value; };
//
//private:
//	type m_value;
//};
//
//
//template <typename In, typename Out>
//Out translate(In source)
//{
//	return Out(source.value());
//};

#endif