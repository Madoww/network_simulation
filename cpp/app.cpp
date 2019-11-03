#include "app.hpp"
#include "Computer.hpp"
#include "Switch.hpp"
#include <iostream>

app::app()
:m_window(sf::VideoMode(800, 600), "SFML window")
{
    std::unique_ptr<Network_device> k1 (new Computer("k1"));
    std::unique_ptr<Network_device> k2 (new Computer("k2"));
    std::unique_ptr<Network_device> s1(new Switch("s1"));
    std::unique_ptr<Network_device> s2(new Switch("s2"));
    devices.add_device(k1);
    devices.add_device(k2);
    devices.add_device(s1);
    devices.add_device(s2);
    cm::set_device("k1");
    cm::set_address("192.168.0.1", 26);
    cm::set_device("k2");
    cm::set_address("192.168.0.3", 26);
    cm::set_device("k1");
    cm::connect_to("s1", 0);
    cm::set_device("k2");
    cm::connect_to("s2", 0);
}

void app::run()
{
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
        }
        
        input.get_input();
        
        m_window.clear();
        m_window.display();
    }
}
app::~app()
{
    if(m_window.isOpen())
        m_window.close();
}
