#ifndef OPTIONS_IPP
#define OPTIONS_IPP
#include <functional>
#include <cstdint>
#include <algorithm>
#include "boost\asio.hpp"
#include "boost\bind.hpp"
#include "boost\timer.hpp"
#include "boost\thread.hpp"
#include "boost\detail\endian.hpp"
#include "boost\icl\discrete_interval.hpp"
#include <boost\core\noncopyable.hpp>
#include "Options.h"

template<typename Ty>
class get_impl;

template<>
class get_impl<stop_bits>
{
public:
	typedef  boost::asio::serial_port::stop_bits impl;
};

#endif





