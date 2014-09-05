#include <dev/Device.hpp>

dev::Device::Device() 
{
	// for list
}
dev::Device::Device(char* name, dev::Driver *driver)
{
	strcpy(m_Name, name);
	m_Driver = driver;
}
