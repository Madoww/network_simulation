//
//  app.hpp
//  network_simulation
//
//  Created by Filip Szafran on 26/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef app_hpp
#define app_hpp

#include <SFML/Graphics.hpp>
#include "InputManager.hpp"
#include "Device_manager.hpp"

class app
{
public:
    ~app();
    app(const app&)=delete;
    app operator=(const app&)=delete;
    inline static app& instance()
    {
        static app instance;
        return instance;
    }
    void run();
private:
    app();
    InputManager& input = InputManager::instance();
    Device_manager& devices = Device_manager::instance();
    sf::RenderWindow m_window;
};

#endif /* app_hpp */
