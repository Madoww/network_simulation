#include "Server.hpp"
#include "Device_manager.hpp"

#define current_device Device_manager::instance().get_current_device()
#define find_device(x) Device_manager::instance().find_device(x)

int Server::searched_for = 0;

Server::Server(const std::string& name)
{
	ports.emplace_back(Port(ports.size()));
	m_name = name;
	ip.set_other_address(m_name);
	m_type = Device_type::Server;
}

void Server::create_website(const Website& site)
{
	for (auto& port : ports)
	{
		if (auto web = dynamic_cast<Web_server*>(find_device(port.get_connection_address().get_address()).get()))
		{
			std::cout << "Website created through: " << m_name << std::endl;
			web->create_website(std::move(site));
		}
	}
}
void Server::add_record(const DNS_record& record)
{
	for (auto& port : ports)
	{
		if (auto dns = dynamic_cast<DNS*>(find_device(port.get_connection_address().get_address()).get()))
		{
			std::cout << "Record added through: " << m_name << std::endl;
			dns->add_record(std::move(record));
		}
	}
}

void Server::set_dhcp_range(const std::string& first_address, short mask, short address_amount)
{
	for (auto& port : ports)
	{
		if (auto dhcp = dynamic_cast<DHCP*>(find_device(port.get_connection_address().get_address()).get()))
		{
			std::cout << "DHCP range set through: " << m_name << std::endl;
			dhcp->set_dhcp_range(first_address, mask, address_amount);
		}
	}
}
void Server::get_dhcp_users()
{
	for (auto& port : ports)
	{
		if (auto dhcp = dynamic_cast<DHCP*>(find_device(port.get_connection_address().get_address()).get()))
		{
			std::cout << "Getting DHCP users through: " << m_name << std::endl;
			dhcp->get_dhcp_users();
		}
	}
}


DHCP::DHCP(const std::string& name)
{
    ports.emplace_back(Port(ports.size()));
    m_name = name;
    ip.set_other_address(m_name);
    m_type = Device_type::DHCP;
}

void Server::set_address(const std::string& address, short mask)
{
    ip.set_address(address,mask);
}

void DHCP::set_dhcp_range(const std::string& first_address,short mask, short address_amount)
{
    if(dhcp_address.set_address(first_address,mask))
    {
        Address max_address;
        max_address.set_address(first_address);
        max_address = max_address+address_amount;
        if(dhcp_address.is_same_network(max_address))
        {
            dhcp_address.set_address(first_address,mask);
            dhcp_range = address_amount;
			std::cout << "DHCP ranged set to: " << dhcp_address.get_address() << ", " << dhcp_address.get_mask() << ", " << dhcp_range << std::endl;
        }
        else
            std::cout<<"Invalid range"<<std::endl;
    }
}
Address DHCP::get_dhcp()
{
    if(used_addresses<dhcp_range){
		if (std::find(users.begin(), users.end(), current_device.get()) != users.end())
			return current_device->get_address();
    Address temp;
    temp.set_address(dhcp_address.get_address(),dhcp_address.get_mask());
        int tester = 0;
    while(std::find(active_addresses.begin(),active_addresses.end(),temp.get_address())!=active_addresses.end())
    {
        temp = temp+1;
        tester++;
    }
    used_addresses++;
    Device_manager::instance().get_current_device()->is_dhcp = true;
    users.push_back(Device_manager::instance().get_current_device().get());
    active_addresses.push_back(temp.get_address());
    return temp;
    }
    else
    {
        std::cout<<"No usable address"<<std::endl;
        return Address();
    }
}

void DHCP::free_address(const std::string& address_to_free)
{
    for(int i = 0; i<active_addresses.size(); i++)
    {
        if(active_addresses[i] == address_to_free)
        {
            active_addresses.erase(active_addresses.begin()+i);
            --used_addresses;
            break;
        }
    }
    for(int i = 0; i<users.size(); i++)
    {
        if(users[i]==current_device.get())
        {
            users.erase(users.begin()+i);
            break;
        }
    }
}

void DHCP::get_dhcp_users()
{
    for(int i = 0; i<users.size(); i++)
    {
        std::cout<<users[i]->get_name()<<"("<<users[i]->get_address().get_address()<<")"<<std::endl;
    }
}
