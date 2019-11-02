#include "Computer.hpp"
#include "Device_manager.hpp"
#include "Switch.hpp"
#define find_device Device_manager::instance().find_device(name)

Computer::Computer(const std::string& name)
{
    m_name = name;
    m_type = Device_type::Computer;
}

void Computer::connect(const std::string& name,int port_id)
{
    if(find_device->get_type()=="Switch")
    {
        dynamic_cast<Switch*>(find_device.get())->get_port(port_id).set_occupied(true);
            connected_to = dynamic_cast<Switch*>(find_device.get());
        connected = true;
    }
}
