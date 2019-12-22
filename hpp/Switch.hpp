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
private:
};

#endif /* Switch_hpp */
