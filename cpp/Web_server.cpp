//
//  Website_manager.cpp
//  network_simulation
//
//  Created by Filip Szafran on 02/12/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "Server.hpp"
#include "Device_manager.hpp"

Web_server::Web_server(const std::string& name)
{
    websites.push_back(Website("0.0.0.1","Invalid website"));
	add_port();
    m_name = name;
    ip.set_other_address(m_name);
    m_type = Device_type::WEB;
}

void Web_server::create_website(const Website& site)
{
    add_port();
    websites.push_back(std::move(site));
    ports[ports.size()-1].connect_device(websites[websites.size()-1].get_address());
}

Website& Web_server::find_website(const std::string& address)
{
    for(auto& site : websites)
        if(site.get_address().get_address() == address)
            return site;
    return websites[0];
}
