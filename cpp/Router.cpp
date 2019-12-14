#include "Router.hpp"

int Router::searched_for = 0;

Router::Router(const std::string& name)
{
	ports.emplace_back(Port(ports.size()));
	m_name = name;
	ip.set_other_address(m_name);
	m_type = Device_type::Router;
}


void Router::set_address(const std::string& ip, short mask)
{
	ports[current_port].set_address(ip, mask);
}