#include <dev/cga_out.hpp>
#include <kernel/video.h>
#include <iob.h>
#include <config.h>

unsigned short *videomem ;		
unsigned short crtc_mem;									
unsigned int scrHeight ;
unsigned int scrWidth ;
unsigned int xpos=0, ypos=0;
namespace dev
{
	StdCgaVideo::StdCgaVideo()
		:  Driver("CGA", "cga", 0, 0, 0x0700, true, true), m_videomem((uint16_t*) 0xb8000)
	{
		scrHeight = 25;
		scrWidth = 80;

		xpos = 0;
		ypos = 0;
	}
	StdCgaVideo::~StdCgaVideo()
	{
	
	}
	/*void StdCgaVideo::ReadChar()
	{
		return *(m_videomem + xpos + ypos * scrWidth); 
	}*/
	void StdCgaVideo::WriteChar(char c)
	{	
		int t = 0;
		
		switch(c)
		{
		case '\r':                         //-> carriage return
			xpos = 0;
			break;
		case '\n':                         // -> newline (with implicit cr) 
			xpos = 0;
			ypos++;
			break;
		case '\t':
			xpos = (m_pos +LIB_TAB_SIZE ) &  ~(LIB_TAB_SIZE - 1);
			break;
		case '\b':                            // -> backspace 
			t = xpos + ypos * scrWidth; 
			if(t > 1) t--;
			
			if(xpos > 0)
			{
				xpos--;
			}
			else if(ypos > 0)
			{
				ypos--;
				xpos = scrWidth - 1;
			}
			*(m_videomem + xpos + ypos * scrWidth) = ' ' | m_color;
			break;
		default:
			if(c < ' ') break;
			*(m_videomem + xpos + ypos * scrWidth) = (uint16_t)c | m_color;
			xpos++;	
			if(xpos >= scrWidth)
			{
				xpos = 0;
				ypos++;
			}
			break;
		};	
		
		if(ypos == scrHeight)
		{
			ScrollUp();
			ypos--;
		}
		
		GotoXY(xpos, ypos);
		
		iodelay();	
	}
	void StdCgaVideo::GotoXY(unsigned short x, unsigned short y)
	{
		xpos = x; ypos = y;	

		unsigned short offset;

		offset = x + y * scrWidth;            
		outb(0x3D4 + 0, 14);             // MSB of offset to CRTC reg 14 
		outb(0x3D4 + 1, offset >> 8);
		outb(0x3D4 + 0, 15);             // LSB of offset to CRTC reg 15 
		outb(0x3D4 + 1, offset);

	}
	void StdCgaVideo::ScrollUp()
	{
		unsigned int t;

		disable();

		for(t = 0; t < scrWidth * (scrHeight - 1); t++)	// scroll every line up 
			*(m_videomem + t) = *(m_videomem + t + scrWidth);
		for(; t < scrWidth * scrHeight; t++)		//clear the bottom line 
			*(m_videomem + t) = ' ' | m_color;

		enable();
	}
	void StdCgaVideo::Write(const char* cp)
	{
		const char *str = cp, *ch;

		for(ch = str; *ch; ch++) 
		{
			if(ch) WriteChar(*ch);
		}
	}
	void StdCgaVideo::Clear()
	{
		unsigned int i;

		for(i = 0; i < (scrWidth * scrHeight); i++)
		{
			m_videomem[i] = (unsigned char) ' ' | m_color ;
		}
		xpos = 0;
		ypos = 0;
	}	
	void StdCgaVideo::TextColor(uint16_t color)
	{
		m_color = (color << 8) | (m_color & 0xF000);
	}
	void StdCgaVideo::BackColor(uint16_t color)
	{
		m_color = (color << 12) | (m_color & 0x0F00);
	}
	bool StdCgaVideo::Probe()
	{
		
		Clear();
		return true;
		
	}
	uint64_t StdCgaVideo::Read(uint8_t *data, uint64_t offset, uint64_t size)
	{
		uint64_t i, j = 0;
		for(i = offset; i< size; i++)
		{
			if(i < (80*25))
			{
			  data[i-offset] =	m_videomem[i];
			  j++;
			}
			else
				break;
		}
		return j;
	}
	uint64_t StdCgaVideo::Write(uint8_t *cp, uint64_t offset, uint64_t size)
	{
		unsigned char *str = cp;
		for(uint64_t i= 0; i < size; i++)
		{
			WriteChar(str[i]);
		}
		
		return size;
	}
}