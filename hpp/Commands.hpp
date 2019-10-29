//
//  Commands.hpp
//  network_simulation
//
//  Created by Filip Szafran on 26/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef Commands_hpp
#define Commands_hpp

#include <string>
#include "Device_manager.hpp"

namespace cm {
void ping(const std::string&);//Doesn't work yet.
void set_device(const std::string&);//change the currently used device.
void set_address(const std::string&);//set address of the currently used device.

void display_address();
}

#endif /* Commands_hpp */
