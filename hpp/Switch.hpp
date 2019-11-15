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


class Switch : public Connectable
{
public:
    Switch(const std::string&);
    void set_address(const std::string&, short mask = -1) override;//Set the address of the current port.
    const Address& find_device(const std::string&)override;//Checks if a device with entered address is connected to any of the ports.
private:
    static int searched_for;
    static std::vector<std::string>devices_checked;
};

#endif /* Switch_hpp */
