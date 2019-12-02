#include "Device_manager.hpp"
#include <iostream>
#include <algorithm>
#include "Switch.hpp"

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

std::unique_ptr<Network_device>& Device_manager::find_device(const std::string& name)
{
    for(auto& device : devices)
    {
        if(device->get_name()==name)
            return device;
    }
    return devices[0];
}
std::unique_ptr<Network_device>& Device_manager::find_device_by_address(const std::string& address)
{
    for(auto& device : devices)
    {
        if(device->get_address().get_address() == address)
            return device;
    }
    return devices[0];
}
std::unique_ptr<Network_device>& Device_manager::find_device_by_type(const std::string& type)
{
    for(auto& device : devices)
    {
        if(device->get_type() == Device_type::Server)
        {
            return device;
        }
    }
    return devices[0];
}
