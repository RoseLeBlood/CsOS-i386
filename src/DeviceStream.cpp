#include <DeviceStream.hpp>
   
DeviceStream::DeviceStream(dev::Device* device)
	: FileStream(device->getName())
{
	m_device = device;
	m_canRead = device->CanRead();
	m_canWrite = device->CanWrite();
	m_canSeek = false;
}
DeviceStream::~DeviceStream()
{

}