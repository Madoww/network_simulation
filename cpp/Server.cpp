#include "Server.hpp"
#include "Device_manager.hpp"

#define current_device Device_manager::instance().get_current_device()
#define find_device(x) Device_manager::instance().find_device(x)

Server::Server(const std::string& name)
{
	add_port();
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
Address Server::get_dhcp()
{
	if (dhcp_enabled)
	{
		for(auto& port : ports)
		if (auto dhcp = dynamic_cast<DHCP*>(find_device(port.get_connection_address().get_address()).get()))
			return dhcp->get_dhcp();
	}
	else
	{
		return current_device->get_address();
	}
}
void Server::set_address(const std::string& address, short mask)
{
    ip.set_address(address,mask);
}

