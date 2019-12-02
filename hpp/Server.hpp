#ifndef Server_hpp
#define Server_hpp

#include <stdio.h>
#include "Network_device.hpp"

enum class ServerType
{
    DHCP = 0
};

class DHCP
{
public:
    void set_dhcp_range(const std::string&,short,short);
    void free_address(const std::string&);
    void get_dhcp_users();
    Address get_dhcp();
protected:
    Address dhcp_address;
    short dhcp_range = 1;
    short used_addresses = 0;
    std::vector<Network_device*> users;
    std::vector<std::string>active_addresses;
};

class Server : public Connectable,public DHCP
{
public:
    Server(const std::string&);
    void set_address(const std::string&, short mask = -1)override;
private:
    static int searched_for;
};

#endif /* Server_hpp */
