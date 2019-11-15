#include "Computer.hpp"
#include "Device_manager.hpp"
#include "Switch.hpp"
#define find_device Device_manager::instance().find_device(name)

Computer::Computer(const std::string& name)
{
    m_name = name;
    m_type = Device_type::Computer;
}


