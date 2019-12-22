#pragma once
#include "Network_device.hpp"

class Router : public Connectable
{
public:
	Router(const std::string&);
	void set_address(const std::string&, short mask = -1) override;//Set the address of the current port.
private:
};