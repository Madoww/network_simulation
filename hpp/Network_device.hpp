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

class Connectable
{
public:
    virtual void connect_device(const Address&, int port_id) = 0;//Check whether a port[port_id] exists and is not occupied, then connect a device.
    virtual bool find_device(const std::string&) = 0;//Checks if a device with entered address is connected to any of the ports.
    virtual void set_port(int id) = 0; //set the currently used port to ID.
    virtual void add_port() = 0; //create a new port.
    
};

class Connecting
{
public:
    virtual void connect(const std::string&,int) = 0; //Check whether the entered device is connectable, if so, connect this device to it.
    bool is_connected(){return connected;}
    Connectable* get_connection(){return connected_to;}
protected:
    Connectable* connected_to;
    bool connected = false;
};

#endif /* Network_device_hpp */
