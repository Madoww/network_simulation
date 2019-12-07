#include "Server.hpp"
#include "Device_manager.hpp"

DNS::DNS(const std::string& name)
{
	ports.emplace_back(Port(ports.size()));
	m_name = name;
	ip.set_other_address(m_name);
	m_type = Device_type::Server;
}

void DNS::add_record(const DNS_record& record)
{
    records.push_back(std::move(record));
    add_port();
    ports[ports.size()-1].connect_device(records[records.size()-1].get_address());
    std::cout<<"DNS: "<<ports[ports.size()-1].get_address().get_address()<<std::endl;
}

const std::string& DNS::find_record(const std::string& name)
{
    for(auto& record : records)
    {
        if(record.get_address().get_address() == name)
            return record.address;
    }
    return "";
}
