#include <dev/timer.hpp>
#include <cxx/iostream.hpp>
#include <kernel/cpuid.hpp>

#include <time.h>
#include <iob.h>
#include <kernel/kernel.hpp>

extern "C" void* kernel_instance;

extern "C" int	 GetDeviceByNameEx(char* name, void** device)
{
	*device = GetDeviceByName(name);
	return *device != NULL;
}
extern "C" void* GetDeviceByName(char* name)
{
	return ((Kernel*)kernel_instance)->GetDriver(name);	
}
extern "C" bool CPUID_IsSupport(uint32_t ext)
{
	return CPUID::IsSupport((cpuid::cpuid_t)ext);
}

extern "C" void sleep(int ms)
{
	dev::StdTimer* timer = (dev::StdTimer*)GetDeviceByName("tm0");
	timer->Sleep(ms);
}
extern "C" int WriteStream(void* stream, uint8_t* data, uint64_t offset, uint64_t size)
{
	IStream *str = (IStream*)stream;
	if(str != NULL)
		return (int)str->Write(data, offset, size);
	return 0;
}
extern "C" int ReadStream(void* stream, uint8_t* data, uint64_t offset, uint64_t size)
{
	IStream *str = (IStream*)stream;
	if(str != NULL)
		return (int)str->Read(data, offset, size);
	return 0;
}
extern "C" int ReadCharStream(void* stream)
{
	IStream *str = (IStream*)stream;
	if(str != NULL)
		return (int)str->ReadChar();
	return 0;
}
extern "C" int WriteCharStream(void* stream, uint8_t data)
{
	IStream *str = (IStream*)stream;
	if(str != NULL)
		str->WriteChar(data);
	return 0;
}
extern "C" int SeekStream(void* stream, uint64_t off, int8_t org)
{
	IStream *str = (IStream*)stream;
	if(str != NULL)
		return (int)str->Seek(off, (SeekOrigin::SeekOrigin_t)org);
	return 0;
}
extern "C" int CanReadStream(void* stream)
{
	IStream *str = (IStream*)stream;
	if(str != NULL)
		return (int)str->CanRead();
	return 0;
}
extern "C" int CanSeekStream(void* stream)
{	
	IStream *str = (IStream*)stream;
	if(str != NULL)
		return (int)str->CanSeek();

	return 0;
}
extern "C" int CanWriteStream(void* stream)
{
	IStream *str = (IStream*)stream;
	if(str != NULL)
		return (int)str->CanWrite();
	return 0;
}
extern "C" void sthreadRun();
extern "C" void sthreadSwitch();