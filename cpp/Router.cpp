#include "Router.hpp"

Router::Router(const std::string& name)
{
	add_port();
	m_name = name;
	ip.set_other_address(m_name);
	m_type = Device_type::Router;
}


void Router::set_address(const std::string& ip, short mask)
{
	ports[current_port].set_address(ip, mask);
}