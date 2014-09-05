#include <dev/key_input.hpp>
#include <iob.h>
#include <cxx/iostream.hpp>
#include <wchar.h>
#include <config.h>

#include KEYBOARD_LANG

#define SHIFT_LEFT              0x2A
#define SHIFT_RIGHT             0x36
#define PAGE_UP                 0x49
#define PAGE_DOWN               0x51
#define LOCK_CAPS               0x3A
#define LOCK_NUM                0x45
#define LED_NUM                 2
#define LED_CAPS                4

namespace dev
{



	   
unsigned short StdKeyboard::sKey()
{
	static unsigned char code, val;
	
	code = inb(KB_DATA_PORT);	// Get scan code
	val =  inb(KB_ACK_PORT);	// Get keyboard acknowledge
	outb(KB_ACK_PORT, val | 0x80); // Disable bit 7
	outb(KB_ACK_PORT, val);	// Send that back

	return( code );
}    



bool StdKeyboard::Probe()
{
	flush();	
	setHandler(IRQ1);
	return true;
}
void StdKeyboard::callback(registers_t *reg)
{
	unsigned short scan_code;
	unsigned char ch;
	
	scan_code=sKey();
	
	
	if (scan_code & 0x80) //keyrelease
	{		
		switch(m_unshifted[scan_code-128])
		{
			case KEY_LSHIFT:
			case KEY_RSHIFT:
				m_shift = 0;
				break;
			case KEY_LCTRL:
			case KEY_RCTRL:
				m_ctrl = 0;
				break;
			case KEY_LALT:
			case KEY_RALT:
				m_alt = 0;
				break;
		}
	}
//key is pressed
	else
	{
		if (m_unshifted[scan_code] == KEY_CAPSLOCK)
		{
			if(m_capslock==0) m_capslock = 1;
			else m_capslock=0;
		}
		if ((m_unshifted[scan_code] == KEY_LSHIFT) || (m_unshifted[scan_code] ==KEY_RSHIFT))
		{
			m_shift = 1;
		}
		if ((m_unshifted[scan_code] == KEY_LCTRL)||(m_unshifted[scan_code] == KEY_RCTRL))
		{
			m_ctrl = 1;
		}
		if ((m_unshifted[scan_code] ==KEY_LALT) || (m_unshifted[scan_code] ==KEY_RALT))
		{
			m_alt = 1;
		}
		if(!m_ctrl || !m_alt)
		{
			if(m_shift)
				ch=m_shifted[scan_code];
			else if(m_capslock)
				ch=m_caps[scan_code];
			else
				ch= (m_unshifted[scan_code]);
		}
		if(buffend!=128)
		{
			buffend++;
		}
		m_buffer[buffend]=ch;
		
	}
}
uint64_t StdKeyboard::Read(uint8_t *data, uint64_t offset, uint64_t size)
{
	for(uint64_t i = 0; i < size; i++)
	{
		data[i] = ReadChar();
	}
	return size;
}
uint64_t StdKeyboard::Write(uint8_t *data, uint64_t offset, uint64_t size)
{
	return 0;
}
char StdKeyboard::ReadChar()
{
	m_buffer[0] = 0;

	while(buffend == 0);
	
	disable();		

	for(int i = 0; i < buffend; i++)
	{
		m_buffer[i] = m_buffer[i + 1];
	}
	buffend--;
	

	enable();

	/*if(m_buffer[0] == ' ')
		return ';*/
 
	return m_buffer[0];
}
void StdKeyboard::setLeds(uint8_t leds)
{
	SendData(0xED);
	SendData(leds);
}
void StdKeyboard::Wait()
{
	int retries = 1000;

	while( ((inb(KB_CMD_PORT) & 0x02) == 0x02) )
	{
		
		if( --retries == 0 )
			break;
	}
}
		
void StdKeyboard::flush()
{
	unsigned temp;
	do
	{
		temp = inb(KB_CMD_PORT);
		if((temp & 0x01) != 0) 
		{
			(void)inb(KB_DATA_PORT);
			continue;
		}
	} while((temp & 0x02) != 0);
}
void StdKeyboard::SendData(unsigned char data)
{
	Wait();	
	outb(KB_DATA_PORT, data);
}
void StdKeyboard::SendCommand(unsigned char c)
{
	Wait();
 	outb(KB_CMD_PORT,c);
}	
}