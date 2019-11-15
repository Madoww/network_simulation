#include "Network_device.hpp"
#include "Device_manager.hpp"
#include <iostream>
#define find_devices Device_manager::instance().find_device(name)

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

const Address& Network_device::get_address()const
{
    return ip;
}
const std::string& Network_device::get_type()
{
    return device_types[static_cast<int>(m_type)];
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
    std::cout<<"Port number: "<<ports.size()<<" successfully added"<<std::endl;
    ports.emplace_back(Port(ports.size()));
}

const Address& Connectable::get_connection_address()const
{
    return ports[current_port].get_connection_address();
}

const Address& Connectable::find_device(const std::string& address)
{
    std::cout<<"Device doesn't support finding a device"<<std::endl;
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
