//
//  Commands.cpp
//  network_simulation
//
//  Created by Filip Szafran on 26/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "Commands.hpp"
#include <iostream>
#include <algorithm>
#include "address.hpp"

namespace cm {
void ping(const std::string& address)
{
    Address ip;
    if(ip.set_address(address))
        std::cout<<"Pinging "<<ip.get_address()<<std::endl;
}
void set_device(const std::string& device)
{
    Device_manager::instance().set_current_device(device);
}
void set_address(const std::string& address)
{
    if(Device_manager::instance().get_current_device()->get_name()!="")
        Device_manager::instance().get_current_device()->set_address(address);
    else
        std::cout<<"No device set"<<'\n';
}

void display_address()
{
   if(Device_manager::instance().get_current_device()->get_name()!="") std::cout<<Device_manager::instance().get_current_device()->get_address().get_address()<<'\n';
    else
        std::cout<<"No device set"<<'\n';
}
}
