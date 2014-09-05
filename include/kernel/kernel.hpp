#ifndef _CSOS_KERNEL_H_PP_
#define _CSOS_KERNEL_H_PP_

#include <kernel/video.h>
#include <kernel/gdt.h>
#include <kernel/multiboot.h>

//#include "fs.h"
//include "initrd.h"
//#include "task.h"
//#include "syscall.h"

#include <sys/utsname.h>
#include <assert.h>

#include <cxx/string.hpp>
#include <cxx/list.hpp>

#include <dev/DriverList.hpp>
#include <dev/DeviceList.hpp>
#include <cxx/stl.hpp>

extern "C" void* kernel_instance;

class Kernel
{
public:
	Kernel(multiboot_info_t *mpt);

	int RunKernel(int args, char** argv);
	
	dev::DriverList* GetDrivers()			
	{ 
		return m_driverList; 
	}
	dev::Driver*	 GetDriver(char* name) 
	{ 
		return GetDevice(name)->getDriver(); 
	}
	
	dev::DeviceManager* GetDevices()
	{ 
		return m_devices; 
	}
	dev::Device*		GetDevice(char* name) 
	{ 
		return m_devices->getDevice(name)->getDevice(); 
	}
	multiboot_info_t*	GetMultiBoot()
	{
		return m_multibootptr;
	}
	
	static Kernel& Instance() { return *((Kernel*)(kernel_instance)); }
private:
	void plotinfo(const char* text, uint32_t s, uint32_t e);
private:
	dev::DriverList*					m_driverList;
	dev::DeviceManager*			    	m_devices;
	multiboot_info_t*					m_multibootptr;
};

extern "C" void* GetDeviceByName(char* name);
extern "C" int	 GetDeviceByNameEx(char* name, void** device);


#endif