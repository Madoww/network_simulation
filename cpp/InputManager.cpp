#include "InputManager.hpp"
#include <iostream>
#include <algorithm>
#include "Device_manager.hpp"
#include "Switch.hpp"
#define function arguments[0]
#define current_device Device_manager::instance().get_current_device()

InputManager::InputManager()
{
    
}

void InputManager::get_input()
{
    std::cout<<'\n'<<":>"<<current_device->get_name()<<"> ";
    if(dynamic_cast<Connectable*>(current_device.get()))
        std::cout<<dynamic_cast<Connectable*>(current_device.get())->get_current_port_id()<<"> ";
    std::getline(std::cin,current_input);
    call_command(current_input);
}

void InputManager::print_input()
{
    std::cout<<current_input;
}
void InputManager::call_command(std::string& command)
{
    argument_count = std::count_if(command.begin(),command.end(),[](char c){return c==' ';})+1;
    //arguments.reserve(3);
    arguments.clear();
    
    std::string current_argument = "";
    command.insert(command.end(), ' ');
    for(int i = 0; i<command.size(); i++)
    {
        if(command[i]!=' ')
        {
            current_argument+=command[i];
        }
        else
        {
            arguments.emplace_back(current_argument);
            current_argument = "";
        }
    }
	if (function == "ping")
		cm::ping(arguments[1]);
	else if (function == "set_device")
		cm::set_device(arguments[1]);
	else if (function == "set_address")
	{
		if (arguments.size() == 2)
			arguments.emplace_back("0");
		cm::set_address(arguments[1], atoi(arguments[2].c_str()));
	}
	else if (function == "set_dhcp_range")
	{
		cm::set_dhcp_range(arguments[1], atoi(arguments[2].c_str()), atoi(arguments[3].c_str()));
	}
	else if (function == "set_address_dhcp")
	{
		cm::set_address_dhcp();
	}
	else if (function == "get_dhcp_users")
		cm::get_dhcp_users();
	else if (function == "get_address")
		cm::display_address();
	else if (function == "get_mask")
		cm::get_mask();
	else if (function == "get_type")
		cm::get_type();
	else if (function == "add_port")
		cm::add_port(arguments[1]);
    else if(function == "add_website")
        cm::add_website(arguments[1], arguments[2]);
	else if (function == "set_port")
		cm::set_port(atoi(arguments[1].c_str()));
    else if(function == "add_record")
        cm::add_record(arguments[1], arguments[2]);
	else if (function == "connect_to")
		cm::connect_to(arguments[1], atoi(arguments[2].c_str()));
	else if (function == "connect")
		cm::connect(arguments[1], atoi(arguments[2].c_str()), arguments[3], atoi(arguments[4].c_str()));
	else if (function == "get_connection_address")
		cm::get_connection();
	else if (function == "get_port_info")
		cm::get_port_info();
    else if(function == "commands")
        cm::commands();
    else
        std::cout<<"Invalid command"<<std::endl;
    for(int i = 0; i<arguments.size(); i++)
        arguments[i]="";
}
