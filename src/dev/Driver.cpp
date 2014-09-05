#include <dev/Driver.hpp>

namespace dev
{
	Driver::Driver() 
	{
	 
	}
	Driver::Driver(char *name, char *devname)
		: m_canread(false), m_canwrite(false), m_off(0), m_pos(0), m_color(0x07)
	{
		strcpy(m_Name, name);
        strcpy(m_DevName, devname);
        
	}
	Driver::Driver(char *name, char *devname, bool canread, bool canwrite)
		: m_canread(canread), m_canwrite(canwrite), m_off(0), m_pos(0), m_color(0x07)
	{
		strcpy(m_Name, name);
        strcpy(m_DevName, devname);
        
	}
	Driver::Driver(char *name, char *devname, int off, int pos, uint16_t cl, 
	               bool canread, bool canwrite)
		: m_canread(canread), m_canwrite(canwrite), m_off(off), m_pos(pos), m_color(cl)
	{
		strcpy(m_Name, name);
        strcpy(m_DevName, devname);
	}
		
	Driver::~Driver()
	{
		set_handler(m_irq, NULL);
	}
	void  Driver::setHandler(uint8_t irq)
	{
		m_irq = irq;
		set_handlerex(irq, driver_callback, this);
	}
	void Driver::unsetHandler(uint8_t irq)
	{
		m_irq = irq;
		set_handler(irq, NULL);
	}
	char * Driver::getDevName()
	{
		return m_DevName;
	}
	void Driver::driver_callback(registers_t* reg, void* userdata)
	{
		Driver* drv = (Driver*)userdata;
		if(drv != NULL)
			drv->callback(reg);
	}	
}
