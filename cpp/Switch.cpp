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

Switch::Switch(const std::string& name)
{
	add_port();
    m_name = name;
    ip.set_other_address(m_name);
    m_type = Device_type::Switch;
}


void Switch::set_address(const std::string& ip, short mask)
{
    ports[current_port].set_address(ip,mask);
}




