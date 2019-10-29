//
//  InputManager.cpp
//  network_simulation
//
//  Created by Filip Szafran on 26/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "InputManager.hpp"
#include <iostream>
#include <algorithm>
#include "Device_manager.hpp"


InputManager::InputManager()
{
    valid_commands = {"ping","set_device","set_address","display_address"};
}

void InputManager::get_input()
{
    std::cout<<'\n'<<":>"<<Device_manager::instance().get_current_device()->get_name()<<"> ";
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
    if(arguments[0] == "ping")
        cm::ping(arguments[1]);
    else if(arguments[0] == "set_device")
        cm::set_device(arguments[1]);
    else if(arguments[0] == "set_address")
        cm::set_address(arguments[1]);
    else if(arguments[0] == "display_address")
        cm::display_address();
    else
        std::cout<<"Invalid command"<<std::endl;
    arguments.clear();
}
