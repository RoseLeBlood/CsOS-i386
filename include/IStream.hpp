#ifndef __SYSTEM_IO_STREAM_HPP__
#define __SYSTEM_IO_STREAM_HPP__

#include <types.h>


namespace SeekOrigin
{
	enum SeekOrigin_t
	{
		Beginn,
		End,
		Current
	};
}

class IStream 
{
public:
	IStream() { }
	IStream(bool canread, bool canwrite, bool canseek) 
		: m_canRead(canread), m_canWrite(canwrite), m_canSeek(canseek) { }
		
	virtual ~IStream() { }

	virtual uint64_t Seek(uint64_t off, SeekOrigin::SeekOrigin_t org) { return 0; }
	
	virtual bool CanRead() { return m_canRead; }
	virtual bool CanSeek() { return m_canSeek; }
	virtual bool CanWrite() { return m_canWrite; }
	
	virtual void Clear() { }
	
	virtual void WriteChar(char c)  { }
	virtual char ReadChar() { return ' '; }
	
	virtual uint64_t Read(uint8_t *data, uint64_t offset, uint64_t size) { return 0; }
	virtual uint64_t Write(uint8_t *data, uint64_t offset, uint64_t size) { return 0; }
protected:
	bool		m_canRead;
	bool		m_canWrite;
	bool 		m_canSeek;
	
};

extern "C"  int WriteStream(void* stream, uint8_t* data, uint64_t offset, uint64_t size);
extern "C"  int ReadStream(void* stream, uint8_t* data, uint64_t offset, uint64_t size);
extern "C"  int ReadCharStream(void* stream);
extern "C"  int WriteCharStream(void* stream, uint8_t data);
extern "C"  int SeekStream(void* stream, uint64_t off, int8_t org);
extern "C"  int CanReadStream(void* stream);
extern "C"  int CanSeekStream(void* stream);
extern "C"  int CanWriteStream(void* stream);

#endif