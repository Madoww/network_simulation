//
//  Network_device.hpp
//  network_simulation
//
//  Created by Filip Szafran on 27/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef Network_device_hpp
#define Network_device_hpp

#include <string>
#include <iostream>
#include "address.hpp"

//Base class for any network device. Not intended to be used on its own
class Network_device
{
public:
    virtual const Address& get_address()const;
    virtual void set_address(const std::string&);//attempt to set the device's address
    virtual const std::string& get_name(){return m_name;}
    virtual ~Network_device(){}
protected:
    Address ip;
    std::string m_name;
};

#endif /* Network_device_hpp */
