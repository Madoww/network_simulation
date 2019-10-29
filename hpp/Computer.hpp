//
//  Computer.hpp
//  network_simulation
//
//  Created by Filip Szafran on 27/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef Computer_hpp
#define Computer_hpp

#include "Network_device.hpp"

class Computer : public Network_device
{
public:
    Computer(const std::string&);
    //void set_address(const std::string&)override;
};

#endif /* Computer_hpp */
