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
void set_address_dhcp();//Set the address of current_device from the DHCP server.
void get_dhcp_users();//If current_device is a DHCP server, prints all its connected users.


void add_port(const std::string& name = "");//Add a port to a currently used device (Must support ports).
void add_website(const std::string& address, const std::string& data);//If current_device is a web_server, add a web site to it.
void add_record(const std::string& name, const std::string& address);//If current_device is a DNS, add a record to id.
void add_device(const std::string& type,const std::string& name);

void install_service(const std::string&, const std::string&);

void display_address();//Print address of current_device.
void get_mask();//Print mask of current_device.
void get_type();//Return the type of the currently used device.
void get_connection();//Get the IP address of the device connected to the currently used port.
void get_port_info();//Print all ports with addresses connected to them.

//help
void commands();//Print all available commands.
}

#endif /* Commands_hpp */
