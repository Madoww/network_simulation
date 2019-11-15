//
//  Router.cpp
//  network_simulation
//
//  Created by Filip Szafran on 09/11/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "Router.hpp"

Router::Router(const std::string& name)
{
    add_port();
    m_name = name;
    ip.set_other_address(name);
    m_type = Device_type::Router;
}
