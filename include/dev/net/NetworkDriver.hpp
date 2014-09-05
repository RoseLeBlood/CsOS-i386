#ifndef DRIVER_NETWORK_HPP
#define DRIVER_NETWORK_HPP

#include <dev/Driver.hpp>
#include <dev/bus/pci_dev.hpp>
#include <dev/bus/pci_entry.hpp>

namespace dev
{
	class NetworkDriver : public Driver
	{
	public:
		NetworkDriver(char* name) : Driver(name, "eth") { }

		
	protected:
		bus::pci_dev*		m_device;
		void*             	m_data; // Drivers internal data
	    uint8_t           	m_MAC[6];
	    //IP_t              IP;
	    //arpTable_t        arpTable;
	    //DHCP_state        DHCP_State;
	    //IP_t              Gateway_IP;
	    //IP_t              Subnet;
	    //IP_t              dnsServer_IP;
	};
}

#endif