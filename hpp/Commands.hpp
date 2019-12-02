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
void connect(const std::string&, int, const std::string&, int);//connect two Connectable devices together.
void set_dhcp_range(const std::string& first_address,short mask, short addresses_amount);
void set_address_dhcp();
void get_dhcp_users();


void add_port(const std::string& name = "");//Add a port to a currently used device (Must support ports).

void display_address();
void get_mask();
void get_type();//Return the type of the currently used device.
void get_connection();//Get the IP address of the device connected to the currently used port.

//help
void commands();
}

#endif /* Commands_hpp */
