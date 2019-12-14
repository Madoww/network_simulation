#include "address.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cctype>

Address::Address()
{
    m_address = "No address set";
}

bool Address::set_address(std::string ip, short mask)
{
    backup = m_address;
    m_address = ip;
    m_mask = 0;
    octets.clear();
    if(std::find_if(ip.cbegin(),ip.cend(),[](unsigned char c){if(c!='.')return !std::isdigit(c);else return false;})!=ip.end())
    {
        return error_while_creating();
    }
    if(std::count_if(ip.cbegin(),ip.cend(),[](char c){return c=='.';})!=3)
    {
        return error_while_creating();
    }
    for(int i = 0; i<ip.size()-1; i++)
    {
        if(ip[i]=='.'&&ip[i+1]=='.')
        {
            return error_while_creating();
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
            return error_while_creating();
        }
    short octet_to_work_on = 1;
    if(octets[0]<= 127)
    {
        m_class = 'A';
        m_default_mask = 8;
    }
    else if(octets[0]<=191)
    {
        m_class = 'B';
        m_default_mask = 16;
        octet_to_work_on = 2;
    }
    else if(octets[0]<=223)
    {
        m_class = 'C';
        m_default_mask = 24;
        octet_to_work_on = 3;
    }
    else if(octets[0]<=239)
        m_class = 'D';
    else
        m_class = 'E';
    if(mask>0 && mask%8!=0)
    {
        m_mask = mask;
    }
    else if(m_class == 'A')
        m_mask = 8;
    else if(m_class == 'B')
        m_mask = 16;
    else if(m_class == 'C')
        m_mask = 24;
    //if(m_mask > m_default_mask)
    {
        short bits_for_network = m_mask - m_default_mask;
        while(bits_for_network>8)
        {
            bits_for_network-=8;
            octet_to_work_on++;
        }
        if(m_mask>m_default_mask)
            octet_to_work_on+=1;
        if(m_mask<m_default_mask)
            return error_while_creating("Masks lower than default masks are not supported");
        {
            sub_network_size = pow(2,8-bits_for_network);
            if(sub_network_size==256)
                sub_network_size = 255;
        }
        if(m_mask > 24)
            octet_to_work_on--;
        if(octets[octet_to_work_on]%sub_network_size==0)
        {
            if(m_mask > 24)
            {
                return error_while_creating();
            }
            if(std::count_if(octets.begin()+octet_to_work_on,octets.end(),[](short x){return x==0;})==4-(octet_to_work_on) || std::count_if(octets.begin()+octet_to_work_on,octets.end(),[](short x){return x==255;})==4-(octet_to_work_on))
            {
                return error_while_creating();
            }
        }
        if(m_mask> 24)
            octet_to_work_on++;
        if((octets[octet_to_work_on-1])%(sub_network_size-1)==0)
        {
            if(std::count_if(octets.begin()+octet_to_work_on,octets.end(),[](short x){return x==0;})==4-(octet_to_work_on) || std::count_if(octets.begin()+octet_to_work_on,octets.end(),[](short x){return x==255;})==4-(octet_to_work_on))
            {
                return error_while_creating();
            }
        }
    }
    return true;
}
void Address::set_other_address(const std::string& name)
{
    m_address = name;
}
const std::string& Address::get_address()const
{
    return m_address;
}

const bool Address::is_same_network(const Address& address)const
{
    if(m_class == address.get_class() && m_mask == address.get_mask() && m_default_mask == address.get_defualt_mask() && m_mask == m_default_mask)
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
            else if(m_class == 'C')
            {
                int count = 0;
                for(int i = 0; i<3; i++)
                    if(octets[i]==address.get_octets()[i])
                        count++;
                if(count==3)
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
        return false;
    }
    return false;
}

bool Address::error_while_creating(const std::string& message)
{
    std::cout<<message<<std::endl;
    m_address = backup;
    return false;
}
