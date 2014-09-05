#include <dev/DeviceList.hpp>
#include <kernel/kernel.hpp>
#include <string.h>
#include <stdio.h>


namespace dev
{
	int	 DeviceManager::getNewPrefix(char* devname)
	{
		char test_name[128];

		for(int i=0 ; i < 255; i++)
		{
			strcpy(test_name, devname);
			strcat(test_name, itoa(i));
			
			if(getDevice(test_name) == NULL)
				return i;
		}
		return -1;
	}

	int                     DeviceManager::ProbeAll()
	{
        m_DeviceList->clear();

        listDriver drv = Kernel::Instance().GetDrivers()->GetDriverList();

		char dev_name[128];


			for(listDriver::iterator i = drv.begin(); i != drv.end(); i++)
			{
				if((*i)->Probe())
				{
					strcpy(dev_name, (*i)->getDevName());
					strcat(dev_name, itoa(getNewPrefix(dev_name)));
					
					m_DeviceList->push_back(new DeviceStream(new Device(dev_name, (*i))));
				}
			}
		
		return m_DeviceList->size();
	}

	bool DeviceManager::addDevice(Device *dev)
	{
		if(getDevice(dev->getName()) != NULL)
		{
			return true;
		}
             
        m_DeviceList->push_back(new DeviceStream(dev));   
        return getDevice(dev->getName()) != NULL;
	}
	DeviceStream *DeviceManager::getDevice(char *name)
	{
		DeviceStream *dr = NULL;
		
		for(listDevices::iterator i = m_DeviceList->begin(); i != m_DeviceList->end(); i++)
    	{
    		if( !strcmp((*i)->getName(), name))
    		{
    			dr = *i;
    			return dr;
    		}
    	}		
    	return NULL;
	}
	unsigned                DeviceManager::getDevicesNumber()
	{
		return m_DeviceList->size();
	}
}