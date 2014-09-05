#ifndef __DEV_CGA_VIDEO_HPP__
#define __DEV_CGA_VIDEO_HPP__

#include <dev/Driver.hpp>

namespace dev
{
	class StdCgaVideo : public Driver
	{
	public:
		StdCgaVideo();
		~StdCgaVideo();

		virtual bool Probe();
		
		virtual void WriteChar(char c);
		virtual void Write(const char* c);
		virtual void GotoXY(unsigned short x, unsigned short y);
		virtual void Clear();
		
		virtual void TextColor(uint16_t color);
		virtual void BackColor(uint16_t color);
		
		virtual uint64_t Read(uint8_t *data, uint64_t offset, uint64_t size);
		virtual uint64_t Write(uint8_t *data, uint64_t offset, uint64_t size);
	protected:
		virtual void ScrollUp();
	protected:
	    uint16_t* m_videomem;
	};
	
	
}
#endif