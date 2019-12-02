#include "Commands.hpp"
#include <iostream>
#include <algorithm>
#include "address.hpp"
#include "Switch.hpp"
#include "Server.hpp"
#include "Performance_tester.hpp"
#define current_device Device_manager::instance().get_current_device()
#define name_device Device_manager::instance().find_device(name)

namespace cm {
std::vector<std::string>valid_commands = {"ping <address>","set_device <name>","set_address <address,mask(def-class)","get_address","get_type","add_port<name(def-current)>"
,"set_port <port_id>","connect_to <name,port_id>","get_connection_address"};
void ping(const std::string& address)
{
    perform_test();
    Address ip;
    if(ip.set_address(address) && dynamic_cast<Connecting*>(current_device.get())->is_connected())
    {
        if(current_device->get_address().is_same_network(dynamic_cast<Connecting*>(current_device.get())->get_connection()->find_device(address)))
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
    {
        if(current_device->is_dhcp)
        {
            dynamic_cast<Server*>(Device_manager::instance().find_device_by_type("Server").get())->free_address(current_device->get_address().get_address());
        }
        Device_manager::instance().get_current_device()->set_address(address,mask);
    }
    else
        std::cout<<"No device set"<<'\n';
}
void set_dhcp_range(const std::string& first_address,short mask, short addresses_amount)
{
    if(current_device->get_type()==Device_type::Server)
    {
        dynamic_cast<Server*>(current_device.get())->set_dhcp_range(first_address, mask, addresses_amount);
    }
}
void get_dhcp_users()
{
    dynamic_cast<Server*>(Device_manager::instance().find_device_by_type("Server").get())->get_dhcp_users();
}
void set_address_dhcp()
{
    //current_device->set_address(dynamic_cast<Server*>(Device_manager::instance().find_device(server_name).get())->get_dhcp().get_address());
    //current_device->set_address(dynamic_cast<Server*>(dynamic_cast<Connecting*>(current_device.get())->get_connection()->find_device(server_name))->get_dhcp());
        if(dynamic_cast<Connectable*>(Device_manager::instance().find_device_by_type("Server").get())->find_device(current_device->get_address().get_address()).get_address()==current_device->get_address().get_address())
        {
            current_device->set_address(dynamic_cast<Server*>(Device_manager::instance().find_device_by_type("Server").get())->get_dhcp().get_address());
        }
    
}
void set_port(int id)
{
    if(dynamic_cast<Connectable*>(current_device.get()))
        dynamic_cast<Connectable*>(current_device.get())->set_port(id);
}
void add_port(const std::string& name)
{
    if(name=="")
    {
        if(dynamic_cast<Connectable*>(current_device.get()))
        {
            dynamic_cast<Connectable*>(current_device.get())->add_port();
        }
        else
            std::cout<<"Cannot add a port"<<std::endl;
    }
    else if(dynamic_cast<Connectable*>(name_device.get()))
    {
        dynamic_cast<Connectable*>(name_device.get())->add_port();
    }
}
void connect_to(const std::string& name, int port_id)
{
    if(dynamic_cast<Connecting*>(current_device.get()))
    {
        dynamic_cast<Connecting*>(current_device.get())->connect(name,port_id);
    }
    else
        std::cout<<"Couldn't connect"<<std::endl;
}
void connect(const std::string& name1, int port_id1, const std::string& name2, int port_id2)
{
    const auto& device1 = dynamic_cast<Connectable*>(Device_manager::instance().find_device(name1).get());
    const auto& device2 = dynamic_cast<Connectable*>(Device_manager::instance().find_device(name2).get());
    if(device1 && device2)
    {
        device1->connect_device(Device_manager::instance().find_device(name2)->get_address(), port_id1);
        device2->connect_device(Device_manager::instance().find_device(name1)->get_address(), port_id2);
    }
}

void display_address()
{
   if(Device_manager::instance().get_current_device()->get_name()!="") std::cout<<Device_manager::instance().get_current_device()->get_address().get_address()<<'\n';
    else
        std::cout<<"No device set"<<'\n';
}
void get_mask()
{
    if(Device_manager::instance().get_current_device()->get_name()!="") std::cout<<Device_manager::instance().get_current_device()->get_address().get_mask()<<'\n';
    else
        std::cout<<"No device set"<<'\n';
}
void get_type()
{
    //std::cout<<Device_manager::instance().get_current_device()->get_type()<<std::endl;
}
void get_connection()
{
    if(dynamic_cast<Connectable*>(current_device.get()))
    {
        std::cout<<dynamic_cast<Connectable*>(current_device.get())->get_connection_address().get_address()<<std::endl;
    }
}

void commands()
{
    for(auto& command : valid_commands)
    {
        std::cout<<command<<std::endl;
    }
}
}
