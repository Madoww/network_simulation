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
    auto& device = find_device;
    if(device->get_type()=="Switch")
    {
        dynamic_cast<Connectable*>(device.get())->connect_device(Device_manager::instance().get_current_device()->get_address(),port_id);
        connected_to = dynamic_cast<Connectable*>(find_device.get());
        connected = true;
    }
}
