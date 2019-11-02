#include "address.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>

Address::Address()
{
    m_address = "No address set";
}

bool Address::set_address(std::string ip, short mask)
{
    std::string backup = m_address;
    m_address = ip;
    m_mask = 0;
    octets.clear();
    if(std::find_if(ip.cbegin(),ip.cend(),[](unsigned char c){if(c!='.')return !std::isdigit(c);else return false;})!=ip.end())
    {
        std::cout<<"Invalid IP address"<<std::endl;
        m_address = backup;
        return false;
    }
    if(std::count_if(ip.cbegin(),ip.cend(),[](char c){return c=='.';})!=3)
    {
        std::cout<<"Invalid IP address"<<std::endl;
        m_address = backup;
        return false;
    }
    for(int i = 0; i<ip.size()-1; i++)
    {
        if(ip[i]=='.'&&ip[i+1]=='.')
        {
            std::cout<<"Invalid IP address"<<std::endl;
            m_address = backup;
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
            m_address = backup;
            return false;
        }
    if(octets[0]<= 127)
    {
        m_class = 'A';
        m_default_mask = 8;
    }
    else if(octets[0]<=191)
    {
        m_class = 'B';
        m_default_mask = 16;
    }
    else if(octets[0]<=223)
    {
        m_class = 'C';
        m_default_mask = 24;
    }
    else if(octets[0]<=239)
        m_class = 'D';
    else
        m_class = 'E';
    if(mask>0)
    {
        m_mask = mask;
    }
    else if(m_class == 'A')
        m_mask = 8;
    else if(m_class == 'B')
        m_mask = 16;
    else if(m_class == 'C')
        m_mask = 24;
    if(m_mask > m_default_mask)
    {
        short temp = m_mask - m_default_mask;
        short network_each;
        short octet = 1;
        if(m_class == 'B')
            octet = 2;
        else if(m_class == 'C')
            octet = 3;
        if(temp == 1)
        {
            network_each = 2;
        }
        else
        {
            network_each = pow(2,temp);
        }
        sub_network_size = network_each;
        if(octets[octet]%network_each==0)
        {
            if(std::count_if(octets.begin()+octet,octets.end(),[](short x){return x==0;})==4-(octet+1))
            {
                std::cout<<"Invalid IP address :("<<std::endl;
                m_address = backup;
                return false;
            }
        }
    }
    return true;
}

const std::string& Address::get_address()const
{
    return m_address;
}

const bool Address::is_same_network(const Address& address)const
{
    if(m_class == address.get_class() && m_mask == address.get_mask() && m_default_mask == address.get_defualt_mask())
    {
        if(m_mask == m_default_mask)
        {
            if(m_class == 'A')
            {
                if(octets[0] == address.get_octets()[0])
                    return true;
            }
            else if(m_class == 'B')
            {
                if(octets[0]==address.get_octets()[0] && octets[1]==address.get_octets()[1])
                    return true;
            }
        }
    }
    else if(m_mask > m_default_mask)
    {
        short octet_min;
        short octet_max;
        short octet_to_use;
        if(m_class == 'A')
            octet_to_use = 1;
        else if(m_class == 'B')
            octet_to_use = 2;
        else if(m_class == 'C')
            octet_to_use = 3;
        if(octets[octet_to_use]>address.get_octets()[octet_to_use])
        {
            octet_min = address.get_octets()[octet_to_use];
            octet_max = octets[octet_to_use];
        }
        else
        {
            octet_max = address.get_octets()[octet_to_use];
            octet_min = octets[octet_to_use];
        }
        for(int i = octet_min+1; i<octet_max+1; i++)
        {
            if(i%sub_network_size==0)
                return false;
        }
        return true;
    }
    else
    {
        std::cout<<"Addresses have different masks."<<std::endl;
        return false;
    }
    return false;
}
