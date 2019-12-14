#include "Network_device.hpp"
#include "Device_manager.hpp"
#include "Server.hpp"
#include <iostream>
#define current_device Device_manager::instance().get_current_device()
#define find_devices Device_manager::instance().find_device(name)
#define server_service_type Device_manager::instance().find_device(port.get_connection_address().get_address())->get_type()

static std::vector<std::string> device_types = {"Computer","Switch"};

void Network_device::set_address(const std::string& address, short mask)
{
    auto backup = ip;
    ip.set_address(address,mask);
    if(dynamic_cast<Connecting*>(this) && dynamic_cast<Connecting*>(this)->is_connected())
    {
        auto obj = dynamic_cast<Connecting*>(this);
        obj->get_connection()->get_connection_port(backup.get_address()).update_connection_address(ip);
    }
}
void Network_device::set_gateway(const std::string& address)
{
    Address temp;
    temp.set_address(address,ip.get_mask());
    if(ip.is_same_network(temp))
        gateway.set_address(address);
    else
        std::cout<<"Gateway is in a different network"<<std::endl;
}
const Address& Network_device::get_address()const
{
    return ip;
}
const Device_type& Network_device::get_type()
{
    return m_type;
}

void Connectable::connect_device(const Address& address, int port_id)
{
    if(port_id<ports.size()){
        if(!ports[port_id].is_occupied())
        {
            std::cout<<m_name<<": ";
            ports[port_id].connect_device(address);
            ports[port_id].set_occupied(true);
        }
        else
            std::cout<<"Port is occupied"<<std::endl;
    }
    else
        std::cout<<"No port available"<<std::endl;
}

void Connectable::set_port(int id)
{
    if(id<ports.size())
        current_port = id;
    else
        std::cout<<"Invalid port"<<'\n';
}

void Connectable::add_port()
{
    //std::cout<<"Port number: "<<ports.size()<<" successfully added"<<std::endl;
    ports.emplace_back(Port(ports.size()));
}

const Address& Connectable::get_connection_address()const
{
    return ports[current_port].get_connection_address();
}

Port& Connectable::get_connection_port(const std::string& address)
{
    for(auto& port : ports)
    {
        if(port.get_connection_address().get_address() == address)
        {
            return port;
        }
    }
}

void Connectable::get_port_info()
{
	for (int i = 0; i < ports.size(); i++)
	{
		std::cout << i << ": " << ports[i].get_connection_address().get_address() << std::endl;
	}
}

void Port::set_id(int id)
{
    port_number = id;
}
void Port::connect_device(const Address& address)
{
    std::cout<<"Connected address: "<<address.get_address()<<std::endl;
    connection_address = address;
}

void Connecting::connect(const std::string& name,int port_id)
{
    auto& device = find_devices;
    if(dynamic_cast<Connectable*>(device.get()))
    {
    dynamic_cast<Connectable*>(device.get())->connect_device(Device_manager::instance().get_current_device()->get_address(),port_id);
        connected_to = dynamic_cast<Connectable*>(find_devices.get());
        connected = true;
    }
}

const Address& Connectable::find_device(const std::string& address)
{
	if (address == "")
	{
		return Address();
	}
    static int searched_for = 0;
    static std::vector<std::string>devices_checked;
    static Connectable* base_switch = nullptr;
    static Connectable* previous_switch = nullptr;
	static bool has_to_be_same_network = true;
    if(auto router = dynamic_cast<Router*>(this))
    {
        if((current_device->get_gateway().get_address() == router->get_port(0).get_address().get_address() &&
           Device_manager::instance().find_device_by_address(address)->get_gateway().get_address() == router->get_port(1).get_address().get_address()) || (current_device->get_gateway().get_address() == router->get_port(1).get_address().get_address() &&
           Device_manager::instance().find_device_by_address(address)->get_gateway().get_address() == router->get_port(0).get_address().get_address()))
        {
            has_to_be_same_network = false;
        }
        else
        {
            previous_switch = nullptr;
            devices_checked.push_back(this->get_address().get_address());
            return base_switch->find_device(address);
        }
    }
    if(base_switch == nullptr)
    {
        base_switch = this;
        /*if(Device_manager::instance().find_device_by_address(address)->get_name()=="")
        {
            base_switch = nullptr;
            searched_for = 0;
            return Address();
        }*/
    }
    if(previous_switch == nullptr)
        previous_switch = this;
    if(searched_for == 0)
    {
        devices_checked.push_back(this->get_address().get_address());
    }
    searched_for++;
    if(searched_for>50)
    {
        searched_for = 0;
        devices_checked.clear();
        previous_switch = nullptr;
        base_switch = nullptr;
		has_to_be_same_network = true;
        return Address();
    }
    for(auto& port : ports)
    {
        if(port.get_connection_address().get_address()==address)
        {
			if (auto dns = dynamic_cast<DNS*>(this))
			{
				has_to_be_same_network = false;
				return base_switch->find_device(dns->find_record(address));
			}
			if (dynamic_cast<Router*>(this))
			{
				has_to_be_same_network = false;
			}
			if (port.get_connection_address().is_same_network(current_device->get_address()) || has_to_be_same_network == false)
			{
				devices_checked.clear();
				searched_for = 0;
				base_switch = nullptr;
				previous_switch = nullptr;
				has_to_be_same_network = true;
				return port.get_connection_address();
			}
        }
    }
    for(auto& port : ports)
    {
        if((Device_manager::instance().find_device(port.get_connection_address().get_address())->get_type()==Device_type::Switch || Device_manager::instance().find_device(port.get_connection_address().get_address())->get_type()==Device_type::Router || server_service_type == Device_type::Server || server_service_type == Device_type::DNS || server_service_type == Device_type::WEB) && std::find(devices_checked.begin(),devices_checked.end(),Device_manager::instance().find_device(port.get_connection_address().get_address())->get_name())==devices_checked.end() && Device_manager::instance().find_device(port.get_connection_address().get_address())->get_name() != previous_switch->get_name())
        {
            previous_switch = this;
            return dynamic_cast<Connectable*>(Device_manager::instance().find_device(port.get_connection_address().get_address()).get())->find_device(address);
        }
    }
    previous_switch = nullptr;
    devices_checked.push_back(this->get_address().get_address());
    return base_switch->find_device(address);
    devices_checked.clear();
    searched_for = 0;
	has_to_be_same_network = true;
    return Address();
}
