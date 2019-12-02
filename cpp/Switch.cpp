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




