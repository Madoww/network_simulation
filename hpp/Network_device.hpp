#ifndef Network_device_hpp
#define Network_device_hpp

#include <string>
#include <iostream>
#include "address.hpp"

enum class Device_type
{
    Computer = 0,
    Switch
};

//Base class for any network device. Not intended to be used on its own
class Network_device
{
public:
    virtual const Address& get_address()const;
    virtual void set_address(const std::string&, short mask = -1);//attempt to set the device's address
    virtual const std::string& get_name(){return m_name;}
    virtual const std::string& get_type();
    virtual ~Network_device(){}
protected:
    Address ip;
    std::string m_name;
    Device_type m_type;
    
};

#endif /* Network_device_hpp */
