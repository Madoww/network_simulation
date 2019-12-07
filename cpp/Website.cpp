//
//  Website.cpp
//  network_simulation
//
//  Created by Filip Szafran on 02/12/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "Website.hpp"

Website::Website(const std::string& address, const std::string& data)
:m_data(data)
{
    ip.set_address(address);
    std::cout<<"Website: "<<ip.get_address()<<" created"<<std::endl;
}

DNS_record::DNS_record(const std::string& name, const std::string& address)
:address(address)
{
    ip.set_other_address(name);
}
