#ifndef __SYSTEM_IO_FILESTREAM_HPP__
#define __SYSTEM_IO_FILESTREAM_HPP__

#include <IStream.hpp>
#include <string.h>
#include <fs.h>
#include <cxx/stl.hpp>

namespace FsFlags
{
	enum FsFlags_t
	{
		File = 0x01,
		Directory = 0x02,
		Device = 0x03
	};
}
class FileStream : public IStream
{
public:
	FileStream() : IStream(true, true, true) 
	{
		m_node = fs_root;
		strcpy(m_name, fs_root->name);
	}
	FileStream(char* name) : IStream(true, true, true) 
	{
		strcpy(m_name, name);
	}
	FileStream(fs_node_t* node)
		: IStream(true, true, true) 
	{
		m_node = node;
		strcpy(m_name, fs_root->name);
	}
	FileStream(fs_node_t* node, bool canread, bool canwrite, bool canseek)
		: IStream(canread, canwrite, canseek) 
	{
		m_node = node;
	}
	virtual void				Open()
	{
		open_fs(m_node, CanRead(), CanWrite());
	}
	virtual void				Close()
	{
		close_fs(m_node);
	}	
	virtual void 				WriteChar(char c)  
	{ 
		uint8_t data[1] = { (uint8_t)(c) };
		Write(data, 0, 1);
	}
	virtual char 				ReadChar() 
	{ 
		uint8_t data[1] = { 0 };
		Read(data, 0, 1);
		return (char)data[0];
	}
	
	virtual uint64_t 			Read(uint8_t *data, uint64_t offset, uint64_t size) 
	{ 
		return read_fs(m_node, data, (uint32_t)offset, (uint32_t)size);
	}
	virtual uint64_t 			Write(uint8_t *data, uint64_t offset, uint64_t size) 
	{ 
		return write_fs(m_node, data, (uint32_t)offset, (uint32_t)size); 
	}

	virtual uint64_t 			Seek(uint64_t offset, SeekOrigin::SeekOrigin_t org) 
	{ 
		return 0;
	}
	
	virtual dirent * 			ReadDir(uint32_t p)
	{ 
		return  readdir_fs(m_node, p);
	}
	virtual FileStream * 		FindDir(char *name)
	{ 
		return new FileStream(finddir_fs(m_node, name));
	}
	
	virtual char *				getName()				{ return m_name; }			
    
               
protected:
	fs_node_t *m_node;
	char m_name[128];
};

#endif