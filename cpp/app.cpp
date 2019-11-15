#include "app.hpp"
#include "Computer.hpp"
#include "Switch.hpp"
#include "Router.hpp"
#include <iostream>

app::app()
:m_window(sf::VideoMode(800, 600), "SFML window")
{
    std::unique_ptr<Network_device> k1 (new Computer("k1"));
    std::unique_ptr<Network_device> k2 (new Computer("k2"));
    std::unique_ptr<Network_device> k3 (new Computer("k3"));
    std::unique_ptr<Network_device> s1(new Switch("s1"));
    std::unique_ptr<Network_device> s2(new Switch("s2"));
    std::unique_ptr<Network_device> s3(new Switch("s3"));
    std::unique_ptr<Network_device> s4(new Switch("s4"));
    std::unique_ptr<Network_device> s5(new Switch("s5"));
    std::unique_ptr<Network_device> r1(new Router("r1"));
    devices.add_device(k1);
    devices.add_device(k2);
    devices.add_device(s1);
    devices.add_device(s2);
    devices.add_device(s3);
    devices.add_device(s4);
    devices.add_device(s5);
    devices.add_device(k3);
    devices.add_device(r1);
    cm::set_device("k1");
    cm::set_address("192.168.0.130");
    cm::set_device("k2");
    cm::set_address("192.168.0.140");
    cm::set_device("k3");
    cm::set_address("192.168.0.150");
    cm::set_device("k1");
    cm::add_port("s1");
    cm::add_port("s1");
    cm::add_port("s2");
    cm::add_port("s3");
    cm::add_port("s3");
    cm::add_port("r1");
    cm::connect_to("s1", 0);
    cm::set_device("k2");
    cm::connect_to("s2", 1);
    cm::set_device("k3");
    cm::connect_to("s5", 0);
    for(int i = 0; i<6; i++)
    {
        cm::add_port("s1");
        cm::add_port("s2");
        cm::add_port("s3");
        cm::add_port("s4");
        cm::add_port("s5");
    }
    cm::connect("s1",4,"s2",4);
    cm::connect("s3", 1, "s2", 5);
    cm::connect("s4",1,"s3",2);
    cm::connect("s5",1,"s3",3);
    //cm::connect("s3",2,"r1",1);
    cm::set_device("k2");
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
