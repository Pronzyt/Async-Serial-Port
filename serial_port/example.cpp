#include <iostream>
#include <thread>
#include <chrono>
#include "AsyncPort.h"


const int send_buf_size = 7;
const char send_buf[send_buf_size] = "Hello\n";


const int receive_buf_size = 100;
char receive_buf[receive_buf_size];


void read_ok(AsyncPort* port);
void read_error(AsyncPort* port, port_error error);
void write_ok(AsyncPort* port);
void write_error(AsyncPort* port, port_error error);


void read_ok(AsyncPort* port)
{
	std::cout << receive_buf;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	port->write(send_buf, send_buf_size, write_ok, write_error);
};


void read_error(AsyncPort* port, port_error error)
{
	std::cout << "read error: " << error.message() << "\n";
};


void write_ok(AsyncPort* port)
{
	port->read(receive_buf, receive_buf_size, read_ok, read_error);
};


void write_error(AsyncPort* port, port_error error)
{
	std::cout << "write error: " << error.message() << "\n";
};


int main()
{
	AsyncPort port;
	port_error error; 

	port.open("COM6", error);
	port.set_flow_control(flow_control(flow_control::none), error);
	port.set_baud_rate(baud_rate(115200), error);
	port.set_parity(parity(parity::none), error);
	port.set_stop_bits(stop_bits(stop_bits::one), error);

	port.write(send_buf, send_buf_size, write_ok, write_error);

	while(true){};

	return 0;
};
