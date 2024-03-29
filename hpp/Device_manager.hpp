#ifndef Device_manager_hpp
#define Device_manager_hpp

#include <memory>
#include "Computer.hpp"
#include "Router.hpp"
#include "Server.hpp"
#include <deque>

class Device_manager
{
public:
    Device_manager(Device_manager&)=delete;
    Device_manager& operator=(Device_manager&)=delete;
    void add_device(std::unique_ptr<Network_device>& device);
    void set_current_device(const std::string&);//Check if a device exists, if so, set it as currently used.
    std::unique_ptr<Network_device>& find_device(const std::string&);//find device by name
    std::unique_ptr<Network_device>& find_device_by_address(const std::string&);
    std::unique_ptr<Network_device>& find_device_by_type(const std::string&);
    std::vector<Server*> find_servers();
    const std::unique_ptr<Network_device>& get_current_device()const{return devices[current_device];}
    //bool is_valid(
    
    inline static Device_manager& instance()
    {
        static Device_manager temp;
        return temp;
    }
private:
    Device_manager();
    std::deque<std::unique_ptr<Network_device>> devices;
    int current_device = -1;
};

#endif /* Device_manager_hpp */
