//
//  address.hpp
//  network_simulation
//
//  Created by Filip Szafran on 27/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef address_hpp
#define address_hpp

#include <string>
#include <vector>

class Address
{
public:
    Address();
    bool set_address(std::string);//attempts to set an address. If fails, address remains unchanged.
    const std::string& get_address()const;
private:
    std::string address;//Holds the address as a string.
    std::vector<short> octets;//Holds the address as separated octets.
};

#endif /* address_hpp */
