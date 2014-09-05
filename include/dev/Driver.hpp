#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__


#include <kernel/isr.h>
#include <IStream.hpp>
#include <string.h>

namespace dev
{
	class Driver 
	{
	public:
		Driver();
		Driver(char *name, char *devname);
		Driver(char *name, char *devname, bool canread, bool canwrite);
		Driver(char *name, char *devname, int off, int pos, uint16_t cl, 
		               bool canread, bool canwrite);
		virtual ~Driver();

		char *	getName() { return m_Name; }
		char *  getDevName();

		void setHandler(uint8_t irq);
		void unsetHandler(uint8_t irq);


		virtual bool Probe() { return true; }
		virtual void GotoXY(unsigned short x, unsigned short y) { }
		virtual void TextColor(uint16_t color) { }
		virtual void BackColor(uint16_t color) { }
		
	
	   /* Für DeviceStream */
		virtual void Clear() { }
	
		virtual void WriteChar(char c)  { }
		virtual char ReadChar() { return ' '; }
	
		virtual uint64_t Read(uint8_t *data, uint64_t offset, uint64_t size) { return 0; }
		virtual uint64_t Write(uint8_t *data, uint64_t offset, uint64_t size) { return 0; }
		
		virtual bool CanRead() { return m_canread; }
		virtual bool CanWrite() { return m_canwrite; }
		
		virtual void callback(registers_t *reg) { }
	protected:
		static void driver_callback(registers_t* reg, void* userdata);
	protected:
		char	m_Name[128];
		char	m_DevName[128];
		bool    m_proved;
		int 	m_irq;
		bool 	m_canread, m_canwrite;
	protected:
	    uint32_t m_off;
	    uint32_t m_pos;
	    uint16_t m_color;
	};
	
}
#endif