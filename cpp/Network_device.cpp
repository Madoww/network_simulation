//
//  Network_device.cpp
//  network_simulation
//
//  Created by Filip Szafran on 27/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "Network_device.hpp"
#include <iostream>



void Network_device::set_address(const std::string& address)
{
    ip.set_address(address);
}

const Address& Network_device::get_address()const
{
    return ip;
}
