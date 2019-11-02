#include "Network_device.hpp"
#include <iostream>

static std::vector<std::string> device_types = {"Computer","Switch"};

void Network_device::set_address(const std::string& address, short mask)
{
    ip.set_address(address,mask);
}

const Address& Network_device::get_address()const
{
    return ip;
}
const std::string& Network_device::get_type()
{
    return device_types[static_cast<int>(m_type)];
}
