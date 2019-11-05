//
//  Switch.cpp
//  network_simulation
//
//  Created by Filip Szafran on 30/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "Switch.hpp"
#include <iostream>

Port::Port(int id)
{
    port_number = id;
}

Switch::Switch(const std::string& name)
{
    ports.emplace_back(Port(ports.size()));
    m_name = name;
    m_type = Device_type::Switch;
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

void Switch::set_address(const std::string& ip, short mask)
{
    ports[current_port].set_address(ip,mask);
}
void Switch::set_port(int id)
{
    if(id<ports.size())
        current_port = id;
    else
        std::cout<<"Invalid port"<<'\n';
}

void Switch::add_port()
{
    std::cout<<"Port number: "<<ports.size()<<" successfully added"<<std::endl;
    ports.emplace_back(Port(ports.size()));
}

const Address& Switch::get_address()const
{
    return ports[current_port].get_address();
}

void Switch::connect_device(const Address& address, int port_id)
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

bool Switch::find_device(const std::string& address)
{
    for(auto& port : ports)
    {
        if(port.get_connection_address().get_address()==address)
            return true;
    }
    return false;
}

const Address& Switch::get_connection_address()
{
    return ports[current_port].get_connection_address();
}
