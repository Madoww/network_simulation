//
//  Switch.cpp
//  network_simulation
//
//  Created by Filip Szafran on 30/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "Switch.hpp"
#include "Device_manager.hpp"
#include <iostream>

int Switch::searched_for = 0;
std::vector<std::string> Switch::devices_checked(0);

Port::Port(int id)
{
    port_number = id;
}

Switch::Switch(const std::string& name)
{
    ports.emplace_back(Port(ports.size()));
    m_name = name;
    ip.set_other_address(m_name);
    m_type = Device_type::Switch;
}


void Switch::set_address(const std::string& ip, short mask)
{
    ports[current_port].set_address(ip,mask);
}





const Address& Switch::find_device(const std::string& address)
{
    static Switch* base_switch = nullptr;
    static Switch* previous_switch = nullptr;
    if(base_switch == nullptr)
    {
        base_switch = this;
    }
    if(previous_switch == nullptr)
        previous_switch = this;
    if(searched_for == 0)
    {
        devices_checked.push_back(this->get_address().get_address());
        std::cout<<"0"<<std::endl;
    }
    searched_for++;
    //for(int i = 0; i<devices_checked.size(); i++)
        //std::cout<<devices_checked[i]<<std::endl;
    if(searched_for>50)
    {
        std::cout<<"Reached max distance"<<std::endl;
        searched_for = 0;
        devices_checked.clear();
        return Address();
    }
    for(auto& port : ports)
    {
        if(port.get_connection_address().get_address()==address)
        {
            devices_checked.clear();
            searched_for = 0;
            return port.get_connection_address();
        }
    }
    for(auto& port : ports)
    {
        if(Device_manager::instance().find_device(port.get_connection_address().get_address())->get_type()=="Switch" && std::find(devices_checked.begin(),devices_checked.end(),Device_manager::instance().find_device(port.get_connection_address().get_address())->get_name())==devices_checked.end() && Device_manager::instance().find_device(port.get_connection_address().get_address())->get_name() != previous_switch->get_name())
        {
//devices_checked.push_back(Device_manager::instance().find_device(port.get_connection_address().get_address())->get_name());
            previous_switch = this;
            return dynamic_cast<Switch*>(Device_manager::instance().find_device(port.get_connection_address().get_address()).get())->find_device(address);
        }
    }
    std::cout<<"NAME: "<<this->get_address().get_address()<<std::endl;
    previous_switch = nullptr;
    devices_checked.push_back(this->get_address().get_address());
    return base_switch->find_device(address);
    devices_checked.clear();
    searched_for = 0;
    return Address();
}
