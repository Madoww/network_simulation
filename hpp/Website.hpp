#ifndef Website_hpp
#define Website_hpp

#include <stdio.h>
#include "address.hpp"
#include "Network_device.hpp"

class Website : public Connecting
{
public:
    Website(const std::string& address, const std::string& data);
private:
    std::string m_data;
};

class DNS_record : public Connecting
{
public:
    DNS_record(const std::string& name, const std::string& address);
    std::string address;
private:
};

#endif /* Website_hpp */
