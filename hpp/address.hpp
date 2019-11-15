#ifndef address_hpp
#define address_hpp

#include <string>
#include <vector>

class Address
{
public:
    Address();
    bool set_address(std::string, short mask = -1);//attempts to set an address. If fails, address remains unchanged.
    const std::string& get_address()const;
    const char& get_class()const{return m_class;}
    const short& get_mask()const{return m_mask;}
    const short& get_defualt_mask()const{return m_default_mask;}
    const bool is_same_network(const Address&)const;//Check whether both addresses are in the same network.
    const std::vector<short>& get_octets()const{return octets;}
    void set_other_address(const std::string&);
private:
    std::string m_address;//Holds the address as a string.
    std::vector<short> octets;//Holds the address as separated octets.
    char m_class;
    short m_default_mask = 0;
    short m_mask = 0;
    short sub_network_size = 0;
    bool error_while_creating(const std::string& message = "Invalid IP address");
    std::string backup;
};

#endif /* address_hpp */
