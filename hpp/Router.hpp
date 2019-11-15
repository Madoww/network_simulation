//
//  Router.hpp
//  network_simulation
//
//  Created by Filip Szafran on 09/11/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef Router_hpp
#define Router_hpp

#include "Network_device.hpp"

class Router : public Connectable
{
public:
    Router(const std::string&);
};

#endif /* Router_hpp */
