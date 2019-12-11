//
//  Website_manager.hpp
//  network_simulation
//
//  Created by Filip Szafran on 02/12/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef Website_manager_hpp
#define Website_manager_hpp

#include <stdio.h>
#include "Website.hpp"

class Website_manager
{
public:
    inline static Website_manager& instance()
    {
        static Website_manager temp;
        return temp;
    }
    void create_website(const Website&);
    Website& find_website(const std::string&);
private:
    Website_manager();
    std::vector<Website> websites;
};

#endif /* Website_manager_hpp */
