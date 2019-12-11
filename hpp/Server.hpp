#ifndef Server_hpp
#define Server_hpp

#include <stdio.h>
#include "Network_device.hpp"
#include "Website.hpp"

enum class ServerType
{
    DHCP = 0
};

class Server : public Connectable
{
public:
	Server(const std::string&);
	void set_address(const std::string&, short mask = -1)override;
	void install_dhcp() { dhcp_enabled = true; }
	void install_dns() { dns_enabled = true; }
	void install_web() { web_enabled = true; }
	void create_website(const Website&);
	void add_record(const DNS_record&);
	void set_dhcp_range(const std::string&, short mask, short address_amount);
	void get_dhcp_users();
private:
	bool dhcp_enabled = false;
	bool dns_enabled = false;
	bool web_enabled = false;
	static int searched_for;
};

class DHCP : public Connectable
{
public:
	DHCP(const std::string&);
    void set_dhcp_range(const std::string& first_address,short mask,short address_amount);
    void free_address(const std::string&);//removes the entered address from the active addresses list.
    void get_dhcp_users();//Prints all devices using a particular DHCP server.
    Address get_dhcp();//Returns a free address from the range. If no address is free, an empty one is returned.
protected:
    Address dhcp_address;
    short dhcp_range = 1;
    short used_addresses = 0;
    std::vector<Network_device*> users;//Pointers to connected devices.
    std::vector<std::string>active_addresses;//Used addresses.
private:
	static int searched_for;
};

class DNS : public Connectable
{
public:
	DNS(const std::string&);
    void add_record(const DNS_record&);//Adds a record containing name(xyz.com) and address
    const std::string& find_record(const std::string& name); //Returns the address of the entered name(xyz.com)
private:
    std::vector<DNS_record> records;
};

class Web_server : public Connectable
{
public:
    Web_server(const std::string&);
    void create_website(const Website&); //Add a website with and address and content
    Website& find_website(const std::string&); //Returns the website with entered address
private:
    std::vector<Website> websites;
};

#endif /* Server_hpp */
