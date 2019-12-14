#ifndef InputManager_hpp
#define InputManager_hpp

#include <string>
#include <vector>
#include "Commands.hpp"

class InputManager
{
public:
    inline static InputManager& instance()
    {
        static InputManager instance;
        return instance;
    }
    InputManager(const InputManager&)=delete;
    InputManager operator=(const InputManager&)=delete;
    void get_input();//take input from the console
    void print_input();//prints the current_input. Used for debuggin purposed.
private:
    InputManager();
    void call_command(std::string&);//Check if the command is valid, then call it.
    std::string current_input;//stores the last entered command.
    std::vector<std::string>valid_commands;//A list of valid commands.
    std::vector<std::string>arguments;//A list of entered arguments(Each ' ' spearates arguments)
    int argument_count = 0;
};

#endif /* InputManager_hpp */
