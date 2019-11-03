//
//  Switch.hpp
//  network_simulation
//
//  Created by Filip Szafran on 30/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef Switch_hpp
#define Switch_hpp

#include "Network_device.hpp"
#include <vector>

//Intended to be used only by the switch class
class Port : public Network_device
{
public:
    void set_occupied(bool status){occupied = status;}
protected:
    Port(int id);
    void set_id(int id);
    int get_id(){return port_number;}
    bool is_occupied(){return occupied;}
    const Address& get_connection_address(){return connection_address;}
    
    void connect_device(const Address&);

    Address address;
    Address connection_address;
    int port_number;
private:
    friend class Switch;
    bool occupied = false;
};

class Switch : public Network_device
{
public:
    Switch(const std::string&);
    void set_address(const std::string&, short mask = -1) override;//Set the address of the current port.
    void set_port(int id);//set the currently used port to ID.
    void add_port();//create a new port.
    void connect_device(const Address&, int port_id);//Check whether a port[port_id] exists and is not occupied.
    
    const Address& get_address()const override;//Return the Address of the currently used port.
    int get_current_port_id(){return ports[current_port].get_id();}
    Port& get_port(int id){return ports[id];}
    bool find_device(const std::string&);//Checks if a device with entered address is connected to any of the ports.
    const Address& get_connection_address();//Returns an address connected to a currently used port.
private:
    std::vector<Port> ports;
    short current_port = 0;
};

#endif /* Switch_hpp */
