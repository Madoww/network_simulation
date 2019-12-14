//
//  Website_manager.cpp
//  network_simulation
//
//  Created by Filip Szafran on 02/12/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "Website_manager.hpp"

Website_manager::Website_manager()
{
    websites.push_back(Website("0.0.0.1","Invalid website"));
}

void Website_manager::create_website(const Website& site)
{
    websites.push_back(std::move(site));
}

Website& Website_manager::find_website(const std::string& address)
{
    for(auto& site : websites)
        if(site.get_address().get_address() == address)
            return site;
    return websites[0];
}
