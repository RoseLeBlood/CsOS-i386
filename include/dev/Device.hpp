#ifndef __DEVICE_DEV_H__
#define __DEVICE_DEV_H__

#include <dev/Driver.hpp>
#include <cxx/iostream.hpp>
#include <string.h>
#include <FileStream.hpp>

namespace dev
{
	class Device 
	{
	public:
		Device();
		Device(char* name, Driver *driver);
		
		virtual ~Device() { }

		char *          getName() 		{ return m_Name; }
		Driver *        getDriver()		{ return m_Driver; }
		char *          getClass()		{ return m_Class; }
		char *          getSubClass()	{ return m_SubClass; }
		
		
		virtual void Clear() 
		{
			 m_Driver->Clear();
		}
		
		virtual void WriteChar(char c) 
		{ 
			m_Driver->WriteChar(c);
		}
		virtual char ReadChar() 
		{ 
			return m_Driver->ReadChar(); 
		}
		
		virtual uint64_t Read(uint8_t *data, uint64_t offset, uint64_t size) 
		{ 
			return m_Driver->Read(data, offset, size); 
		}
		virtual uint64_t Write(uint8_t *data, uint64_t offset, uint64_t size) 
		{ 
			return m_Driver->Write(data, offset, size); 
		}
		virtual bool CanRead() 
		{ 
			return m_Driver->CanRead(); 
		}
		virtual bool CanWrite() 
		{ 
			return m_Driver->CanWrite(); 
		}
		virtual void GotoXY(unsigned short x, unsigned short y) 
		{ 
			m_Driver->GotoXY(x,y);
		}
		virtual void TextColor(uint16_t color) 
		{
			m_Driver->TextColor(color); 
		}
		virtual void BackColor(uint16_t color) 
		{ 
			m_Driver->BackColor(color); 
		}
	private:
		char            			m_Name[128];                    ///< Name of the device (like hd0, eth0)
		char            			m_Class[128];                   ///< Class
		char            			m_SubClass[128];                ///< Sub class
		Driver *        			m_Driver;                               ///< Driver of the device
	};
}
#endif