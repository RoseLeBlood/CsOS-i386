#ifndef __DEVICE_LIST_H__
#define __DEVICE_LIST_H__

#include <cxx/common.hpp>
#include <cxx/algorithm.hpp>
#include <cxx/list.hpp>

#include <DeviceStream.hpp>


namespace dev
{
	typedef std::list<DeviceStream*> listDevices;

	class DeviceManager
	{
	public:
		DeviceManager()
		{
			m_DeviceList = new listDevices();
		}
		~DeviceManager()
		{
			delete m_DeviceList;
		}
		int						ProbeAll();
		
		bool                    addDevice(Device *dev); // add 
		DeviceStream *          getDevice(char *name);
		unsigned                getDevicesNumber();
		
		listDevices*			getList() { return m_DeviceList; }
	private:
		int					getNewPrefix(char* devname);
	private:
		listDevices*  m_DeviceList;
	};
}



#endif