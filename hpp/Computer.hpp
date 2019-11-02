#ifndef Computer_hpp
#define Computer_hpp

#include "Network_device.hpp"
#include "Switch.hpp"

class Computer : public Network_device
{
public:
    Computer(const std::string&);
    void connect(const std::string&,int);
    bool is_connected(){return connected;}
    Switch* get_connection(){return connected_to;}
private:
    Switch* connected_to;
    bool connected = false;
};

#endif /* Computer_hpp */
