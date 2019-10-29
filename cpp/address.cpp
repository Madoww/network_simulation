//
//  address.cpp
//  network_simulation
//
//  Created by Filip Szafran on 27/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "address.hpp"
#include <iostream>
#include <algorithm>

Address::Address()
{
    address = "No address set";
}

bool Address::set_address(std::string ip)
{
    std::string backup = address;
    address = ip;
    octets.clear();
    if(std::count_if(ip.begin(),ip.end(),[](char c){return c=='.';})!=3)
    {
        std::cout<<"Invalid IP address"<<std::endl;
        return false;
    }
    for(int i = 0; i<ip.size()-1; i++)
    {
        if(ip[i]=='.'&&ip[i+1]=='.')
        {
            std::cout<<"Invalid IP address"<<std::endl;
            return false;
        }
    }
    std::string temp_address = "";
    ip+='.';
    for(int i = 0; i<ip.size(); i++)
    {
        if(ip[i]!='.')
            temp_address+=ip[i];
        else
        {
            short tmp = atoi(temp_address.c_str());
            octets.push_back(tmp);
            temp_address="";
        }
    }
        if(std::find_if(octets.begin(),octets.end(),[](short a){return a>255||a<0;})!=octets.end())
        {
            std::cout<<"Invalid IP address :("<<std::endl;
            address = backup;
            return false;
        }
    return true;
}

const std::string& Address::get_address()const
{
    return address;
}
