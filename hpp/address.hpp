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
private:
    std::string m_address;//Holds the address as a string.
    std::vector<short> octets;//Holds the address as separated octets.
    std::vector<short>default_address;
    char m_class;
    short m_default_mask = 0;
    short m_mask = 0;
    short sub_network_size = 0;
};

#endif /* address_hpp */
