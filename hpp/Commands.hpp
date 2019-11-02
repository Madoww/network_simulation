#ifndef Commands_hpp
#define Commands_hpp

#include <string>
#include "Device_manager.hpp"

namespace cm {
void ping(const std::string&);//Doesn't work yet.
void set_device(const std::string&);//change the currently used device.
void set_address(const std::string&, int mask = 0);//set address of the currently used device.
void set_port(int id);//set the currently used port (device must suppor ports).
void connect_to(const std::string&, int);//Connect two devices together.


void add_port();//Add a port to a currently used device (Must support ports).

void display_address();
void get_type();//Return the type of the currently used device.
void get_connection();//Get the IP address of the device connected to the currently used port.
}

#endif /* Commands_hpp */
