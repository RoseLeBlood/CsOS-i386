#ifndef __SYSTEM_IO_DEVICESTREAM_HPP__
#define __SYSTEM_IO_DEVICESTREAM_HPP__

#include <FileStream.hpp>
#include <dev/Device.hpp>

class DeviceStream : public FileStream
{
public:
	DeviceStream(dev::Device* device);
	virtual ~DeviceStream();

	virtual void				Open()
	{
	}
	virtual void				Close()
	{
	}	
	virtual void 				WriteChar(char c)  
	{ 
		return m_device->WriteChar(c);
	}
	virtual char 				ReadChar() 
	{ 
		return m_device->ReadChar();
	}
	
	virtual uint64_t 			Read(uint8_t *data, uint64_t offset, uint64_t size) 
	{ 
		return m_device->Read(data, offset, size);
	}
	virtual uint64_t 			Write(uint8_t *data, uint64_t offset, uint64_t size) 
	{ 
		return m_device->Write(data, offset, size); 
	}

	virtual uint64_t 			Seek(uint64_t offset, SeekOrigin::SeekOrigin_t org) 
	{ 
		return -1; 
	}
	
	virtual dirent * 			ReadDir(uint32_t p)
	{ 
		return NULL; 
	}
	virtual FileStream * 		FindDir(char *name)
	{ 
		return NULL;
	}
    
    dev::Device*				getDevice() { return m_device; }  
    dev::Driver*				getDriver() { return m_device->getDriver(); }
protected:
	dev::Device*		m_device;
};
#endif