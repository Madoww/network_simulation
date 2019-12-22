#ifndef Network_device_hpp
#define Network_device_hpp

#include <string>
#include <iostream>
#include "address.hpp"

enum class Device_type
{
    Computer = 0,
    Switch,
    Server,
	DHCP,
	DNS,
	WEB,
    Router
};

//Base class for any network device. Not intended to be used on its own
class Network_device
{
public:
    const Address& get_address()const;
    virtual void set_address(const std::string&, short mask = -1);//attempt to set the device's address
    virtual void set_gateway(const std::string&);
    const Address& get_gateway()const{return gateway;}
    const std::string& get_name(){return m_name;}
    const Device_type& get_type();
    bool is_dhcp = false;
    virtual ~Network_device(){}
protected:
    Address ip;
    Address gateway;
    std::string m_name;
    Device_type m_type;
	static int searched_for;
    
};
//Intended to be used only by the Connectable class
class Port : public Network_device
{
public:
    void set_occupied(bool status){occupied = status;}
    void update_connection_address(const Address& address){connection_address=address;}
	void set_id(int id);
	int get_id() { return port_number; }
	bool is_occupied() { return occupied; }
	const Address& get_connection_address()const { return connection_address; }
	void connect_device(const Address&);
protected:
    Port(int id);
    Address connection_address; //Address of the device connected to this port.
    int port_number;
private:
    friend class Connectable;
    bool occupied = false;
};

class Connectable : public Network_device
{
public:
    void connect_device(const Address&, int port_id);//Check whether a port[port_id] exists and is not occupied, then connect a device.
    const Address& find_device(const std::string&);//Checks if a device with entered address is connected to any of the ports recursively.
    void set_port(int id); //set the currently used port to ID.
    void add_port(); //create a new port.
	void get_port_info();//prints connection addresses of all ports.
    int get_current_port_id(){return ports[current_port].get_id();}
    const Address& get_connection_address()const;//Returns an address connected to a currently used port.
    Port& get_port(int id){return ports[id];}
    Port& get_connection_port(const std::string&);//returns the port connected to a device with entered address.
	int get_last_port_id() { return ports.size() - 1; }
protected:
    std::vector<Port>ports;
    short current_port = 0;
    virtual ~Connectable(){}
};

class Connecting : public Network_device
{
public:
    void connect(const std::string&,int); //Check whether the entered device is connectable, if so, connect this device to it.
    bool is_connected(){return connected;}
    Connectable* get_connection(){return connected_to;}
protected:
    Connectable* connected_to;
    bool connected = false;
	virtual ~Connecting(){}
};

#endif /* Network_device_hpp */
