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
std::vector<std::string>valid_commands = {
    "ping <address>",
    "set_device <name>",
    "set_address <address>,mask(def<-class)",
    "set_port <port_id>",
    "connect_to <name,port_id>",
    "connect <name1,port_id1,name2,port_id2>",
    "set_dhcp_range <first_address,mask,address_count>",
    "set_address_dhcp",
    "get_dhcp_users",
    "add_port <device_name(def<-current)>",
    "add_website <address,data>",
    "add_record <name,address>",
    "get_address",
    "get_mask",
    "get_type",
    "get_connection_address",
    "get_port_info"
};
void ping(const std::string& address)
{
    perform_test();
    Address ip;
    ip.set_other_address(address);
    if(dynamic_cast<Connecting*>(current_device.get())->is_connected())
    {
        if(auto device = dynamic_cast<Connecting*>(current_device.get())->get_connection()->find_device(address); device.get_address()!="" && Address(device.get_address()).is_valid())
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
            dynamic_cast<DHCP*>(Device_manager::instance().find_device_by_type("Server").get())->free_address(current_device->get_address().get_address());
        }
        Device_manager::instance().get_current_device()->set_address(address,mask);
    }
    else
        std::cout<<"No device set"<<'\n';
    if(auto device = dynamic_cast<Connectable*>(current_device.get()))
    {
        device->get_port(device->get_current_port_id()).set_address(address,mask);
    }
}
void set_gateway(const std::string& address)
{
    current_device->set_gateway(address);
}
void set_address_dhcp()
{
	if (auto device = dynamic_cast<Connecting*>(current_device.get()); device->is_connected())
	{
		for (auto server : Device_manager::instance().find_servers())
		{
			if (device->get_connection()->find_device(server->get_address().get_address()).is_valid())
			{
                Address temp = server->get_dhcp();
				current_device->set_address(temp.get_address(),temp.get_mask());
			}
		}
	}
}
void set_dhcp_range(const std::string& first_address,short mask, short addresses_amount)
{
    if(current_device->get_type()==Device_type::DHCP)
    {
        dynamic_cast<DHCP*>(current_device.get())->set_dhcp_range(first_address, mask, addresses_amount);
    }
	if (auto server = dynamic_cast<Server*>(current_device.get()))
	{
		server->set_dhcp_range(first_address, mask, addresses_amount);
	}
}
void get_dhcp_users()
{
	if (current_device->get_type() == Device_type::DHCP)
	{
		dynamic_cast<DHCP*>(current_device.get())->get_dhcp_users();
	}
	if (auto server = dynamic_cast<Server*>(current_device.get()))
	{
		server->get_dhcp_users();
	}
}

void set_port(int id)
{
    if(auto connectable = dynamic_cast<Connectable*>(current_device.get()))
        connectable->set_port(id);
}
void add_port(const std::string& name)
{
    if(name=="")
    {
        if(auto connectable = dynamic_cast<Connectable*>(current_device.get()))
        {
            connectable->add_port();
        }
        else
            std::cout<<"Cannot add a port"<<std::endl;
    }
    else if(auto connectable = dynamic_cast<Connectable*>(name_device.get()))
    {
        connectable->add_port();
    }
}

void add_website(const std::string& address, const std::string& data)
{
    if(auto web_server = dynamic_cast<Web_server*>(current_device.get()))
    {
        web_server->create_website(Website(address,data));
    }
	if (auto server = dynamic_cast<Server*>(current_device.get()))
	{
		server->create_website(Website(address, data));
	}
}
void add_record(const std::string& name, const std::string& address)
{
    if(auto dns_server = dynamic_cast<DNS*>(current_device.get()))
    {
        dns_server->add_record(DNS_record(name,address));
    }
	if (auto server = dynamic_cast<Server*>(current_device.get()))
	{
		server->add_record(DNS_record(name, address));
	}
}
void add_device(const std::string& type, const std::string& name)
{
	std::unique_ptr<Network_device> temp;
	if(type == "computer")
	{
		temp = std::make_unique<Computer>(name);
	}
	else if (type == "switch")
		temp = std::make_unique<Switch>(name);
	else if (type == "server")
		temp = std::make_unique<Server>(name);
	if (temp.get() != nullptr)
	{
		std::cout << "Device added successfully" << std::endl;
		Device_manager::instance().add_device(temp);
	}
	else
		std::cout << "Failed to add a device" << std::endl;
}
void install_service(const std::string& service_name, const std::string& device_name)
{
	if(current_device->get_type() == Device_type::Server)
	{
		std::unique_ptr<Network_device> temp;
		auto server = dynamic_cast<Server*>(current_device.get());
		if (service_name == "dns")
		{
			temp = std::make_unique<DNS>(device_name);
			server->install_dns();
		}
		else if (service_name == "dhcp")
		{
			temp = std::make_unique<DHCP>(device_name);
			server->install_dhcp();
		}
		else if (service_name == "web_server")
		{
			temp = std::make_unique<Web_server>(device_name);
			server->install_web();
		}
		Device_manager::instance().add_device(temp);
		server->add_port();
		connect(current_device->get_name(), server->get_last_port_id(), device_name, 0);
	}
}

void connect_to(const std::string& name, int port_id)
{
    if(auto device = dynamic_cast<Connecting*>(current_device.get()))
    {
        device->connect(name,port_id);
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
	if (Device_manager::instance().get_current_device()->get_name() != "")
	{
        if(auto device = dynamic_cast<Connectable*>(current_device.get()))
            std::cout<<device->get_port(device->get_current_port_id()).get_address().get_address()<<std::endl;
        else
		std::cout << Device_manager::instance().get_current_device()->get_address().get_address() <<", "<< Device_manager::instance().get_current_device()->get_address().get_mask() << '\n';
	}
    else
        std::cout<<"No device set"<<'\n';
}
void get_mask()
{
    if(Device_manager::instance().get_current_device()->get_name()!="") std::cout<<current_device->get_address().get_mask()<<'\n';
    else
        std::cout<<"No device set"<<'\n';
}
void get_gateway()
{
    if(Device_manager::instance().get_current_device()->get_name()!="")
        std::cout<<current_device->get_gateway().get_address()<<std::endl;
    else
        std::cout<<"No device set"<<'\n';
}
void get_type()
{
    //std::cout<<Device_manager::instance().get_current_device()->get_type()<<std::endl;
}
void get_connection()
{
    if(auto device = dynamic_cast<Connectable*>(current_device.get()))
    {
        std::cout<<device->get_connection_address().get_address()<<std::endl;
    }
	else if (auto device = dynamic_cast<Connecting*>(current_device.get()))
	{
		std::cout << device->get_connection()->get_address().get_address() << std::endl;
	}
}
void get_port_info()
{
	if (auto device = dynamic_cast<Connectable*>(current_device.get()))
	{
		 device->get_port_info();
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
