//
//  Device_manager.cpp
//  network_simulation
//
//  Created by Filip Szafran on 27/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "Device_manager.hpp"
#include <iostream>
#include <algorithm>

Device_manager::Device_manager()
{
    std::unique_ptr<Network_device> empty(new Computer(""));
    add_device(empty);
    set_current_device("");
}

void Device_manager::add_device(std::unique_ptr<Network_device>& device)
{
    devices.push_back(std::move(device));
}

void Device_manager::set_current_device(const std::string& name)
{
    bool found = false;
    for(int i = 0; i<devices.size(); i++)
    {
        if(devices[i]->get_name()==name)
        {
            found = true;
            current_device = i;
            break;
        }
    }
    if(!found)
        std::cout<<"No device found"<<std::endl;
}
