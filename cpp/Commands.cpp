#include "Commands.hpp"
#include <iostream>
#include <algorithm>
#include "address.hpp"
#include "Switch.hpp"
#define current_device Device_manager::instance().get_current_device()

namespace cm {
void ping(const std::string& address)
{
    Address ip;
    if(ip.set_address(address) && dynamic_cast<Computer*>(current_device.get())->is_connected())
    {
        if(dynamic_cast<Computer*>(current_device.get())->get_connection()->find_device(address) && current_device->get_address().is_same_network(ip))
            for(int i = 0; i<1; i++)
            {
                std::cout<<"Reply from "<<address<<std::endl;
            }
        else
            for(int i = 0; i<1; i++)
            {
                std::cout<<"Request timed out"<<std::endl;
            }
    }
}
void set_device(const std::string& device)
{
    Device_manager::instance().set_current_device(device);
}
void set_address(const std::string& address, int mask)
{
    if(Device_manager::instance().get_current_device()->get_name()!="")
        Device_manager::instance().get_current_device()->set_address(address,mask);
    else
        std::cout<<"No device set"<<'\n';
}
void set_port(int id)
{
    if(current_device->get_type() == "Switch")
        dynamic_cast<Switch*>(current_device.get())->set_port(id);
}
void add_port()
{
    if(current_device->get_type() == "Switch")
    {
        dynamic_cast<Switch*>(current_device.get())->add_port();
    }
    else
        std::cout<<"Cannot add a port"<<std::endl;
}
void connect_to(const std::string& name, int port_id)
{
    auto& device = Device_manager::instance().find_device(name);
    if(device->get_type()=="Switch")
    {
        dynamic_cast<Switch*>(device.get())->connect_device(current_device->get_address(),port_id);
        dynamic_cast<Computer*>(current_device.get())->connect(name,port_id);
    }
    else
        std::cout<<"Couldn't connect"<<std::endl;
}

void display_address()
{
   if(Device_manager::instance().get_current_device()->get_name()!="") std::cout<<Device_manager::instance().get_current_device()->get_address().get_address()<<'\n';
    else
        std::cout<<"No device set"<<'\n';
}
void get_type()
{
    std::cout<<Device_manager::instance().get_current_device()->get_type()<<std::endl;
}
void get_connection()
{
    if(current_device->get_type()=="Switch")
    {
        std::cout<<dynamic_cast<Switch*>(current_device.get())->get_connection_address().get_address()<<std::endl;
    }
}
}
