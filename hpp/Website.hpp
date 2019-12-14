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

//Contains a name of a website (e.g. xyz.com) and its address.
class DNS_record : public Connecting
{
public:
    DNS_record(const std::string& name, const std::string& address);
    const std::string& get_record_address(){return address;}
private:
    std::string address;
};

#endif /* Website_hpp */
