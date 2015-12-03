#include "AsyncSimplePort.h"
#include "Options.h"


//std::array<char, 7> buf;
//
//void read_handler()
//{
//	std::cout << std::string(buf.data());
//}


int main()
{
	try{
		AsyncPortImpl port;
		//std::cout << "Name: ";

		//std::string s;
		//std::cin >> s;
		AsyncPortImpl::error_code error = port.open("COM6");
		port.set_option(stop_bits(stop_bits::one));
		if (error.value() == 0)
		{
			std::cout << "OK" << "\n";
		}
		else
		{
			std::cout << "FAIL" << "\n";
		}
		//std::string s = error.message();
		port.close();
		//port.write("HELLO\n", 7, [](){}, [](port_error err){});
		//std::array<char, 7> buf;
		//port.read(buf.data(), 7, [&buf](){std::cout << std::string(buf.data()); }, [](port_error err){});
	}
	catch (boost::system::system_error e)
	{
		std::string s = e.what();
		std::cout << "FAIL" << "\n";
	};
	char ch;
	std::cin >> ch;
	return 0;
}