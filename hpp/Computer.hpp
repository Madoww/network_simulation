#ifndef Computer_hpp
#define Computer_hpp

#include "Network_device.hpp"
#include "Switch.hpp"

class Computer : public Connecting
{
public:
    Computer(const std::string&);
    //void connect(const std::string&,int)override;//Check whether the entered device is connectable, if so, connect this device to it.
};

#endif /* Computer_hpp */
