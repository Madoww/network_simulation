#include "app.hpp"
#include "Computer.hpp"
#include "Switch.hpp"
#include "Server.hpp"
#include <iostream>

app::app()
{
    std::unique_ptr<Network_device> k1 (new Computer("k1"));
    std::unique_ptr<Network_device> k2 (new Computer("k2"));
    std::unique_ptr<Network_device> k3 (new Computer("k3"));
    std::unique_ptr<Network_device> s1(new Switch("s1"));
    std::unique_ptr<Network_device> s2(new Switch("s2"));
    std::unique_ptr<Network_device> s3(new Switch("s3"));
    std::unique_ptr<Network_device> s4(new Switch("s4"));
    std::unique_ptr<Network_device> s5(new Switch("s5"));
    std::unique_ptr<Network_device> sv(new DHCP("server"));
	std::unique_ptr<Network_device> dns(new DNS("dns"));
    std::unique_ptr<Network_device> web(new Web_server("web"));
    dynamic_cast<Web_server*>(web.get())->create_website(Website("192.168.0.10","Data"));
    dynamic_cast<DHCP*>(sv.get())->set_dhcp_range("192.168.0.1", 24, 20);
    dynamic_cast<DNS*>(dns.get())->add_record(DNS_record("wp.pl","192.168.0.10"));
    //dynamic_cast<DNS*>(dns.get())->add_record(DNS_record("onet.pl","192.168.0.11"));
    devices.add_device(k1);
    devices.add_device(k2);
    devices.add_device(s1);
    devices.add_device(s2);
    devices.add_device(s3);
    devices.add_device(s4);
    devices.add_device(s5);
    devices.add_device(k3);
    devices.add_device(sv);
	devices.add_device(dns);
    devices.add_device(web);
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
    cm::connect_to("s1", 0);
    cm::set_device("k2");
    cm::connect_to("s2", 1);
	cm::add_port("server");
	cm::add_port("server");
    cm::add_port("server");
    cm::add_port("web");
	cm::add_port("dns");
	cm::add_port("dns");
    for(int i = 0; i<6; i++)
    {
        cm::add_port("s1");
        cm::add_port("s2");
        cm::add_port("s3");
        cm::add_port("s4");
        cm::add_port("s5");
    }
    cm::set_device("k3");
    cm::connect_to("s4", 2);
    cm::connect("s1",4,"s2",4);
    cm::connect("s3", 1, "s2", 5);
    cm::connect("s4",1,"s3",2);
    cm::connect("s5",1,"s3",3);
    cm::connect("server",0,"s5",3);
	cm::connect("dns", 3, "server", 2);
    cm::connect("web",0,"server",3);
    //cm::connect("s3",2,"r1",1);
    cm::set_device("server");
    cm::set_dhcp_range("192.168.0.1", 24, 30);
    cm::set_device("k1");
    cm::set_address_dhcp();
    cm::set_device("k2");
    cm::set_address_dhcp();
    cm::set_device("k3");
    cm::set_address_dhcp();
}

void app::run()
{
    while (true)
    {
		input.get_input();
    }
}
app::~app()
{
  
}
