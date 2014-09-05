#include <dev/serial_out.hpp>
#include <iob.h>
#include <kernel/video.h>
#include <stdio.h>

using namespace dev;
SerialOut::SerialOut(int port) : Driver("Serial i/o", "sr", 0,0,0x07, true, true), m_port(port)
{ 
	/*
    COM1: I/O port 0x3F8, IRQ 4
    COM2: I/O port 0x2F8, IRQ 3
    COM3: I/O port 0x3E8, IRQ 4
    COM4: I/O port 0x2E8, IRQ 3
*/
	switch(m_port)
	{
	case 0x3E8:
	case 0x3F8:
		m_irq = IRQ4;
		break;
	case 0x2F8:
	case 0x2E8:
		m_irq = IRQ3;
		break;
	default:
		m_irq = -1;
	}
	
	sprintf(m_Name, "%s ( 0x%X : %d )", m_Name, port, m_irq);
}

bool SerialOut::Probe()
{
	if(m_irq == -1)
		return false;
		
	outb(m_port + 1, 0x00);    // Disable all interrupts
  	outb(m_port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
  	outb(m_port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
  	outb(m_port + 1, 0x00);    //                  (hi byte)
  	outb(m_port + 3, 0x03);    // 8 bits, no parity, one stop bit
  	outb(m_port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
  	outb(m_port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
  	outb(m_port + 1, 0x0C);    // enable all interrupts.
  	
  	
	return true;
	
}
		
void SerialOut::WriteChar(char c)
{
	while (!readyToTransmit())
	{
	}

	outb(m_port, c);
}
void SerialOut::Write(const char* c)
{	
	startColor();
	const char *str = c, *ch;

	for(ch = str; *ch; ch ++) 
	{
		/*if(ch)*/ WriteChar(*ch);
	}
	endColor();
}
void SerialOut::InternalWrite(const char* c)
{
	const char *str = c, *ch;

	for(ch = str; *ch; ch ++) 
	{
		/*if(ch)*/ WriteChar(*ch);
	}
}
void SerialOut::GotoXY(unsigned short x, unsigned short y)
{

}
void SerialOut::Clear()
{
	InternalWrite("\\033c"); 
}

void SerialOut::TextColor(uint16_t color)
{
	m_color = color;
}
void SerialOut::BackColor(uint16_t color)
{
	m_bcolor = color;
}	

uint64_t SerialOut::Read(uint8_t *data, uint64_t offset, uint64_t size)
{
	return 0;
}
uint64_t SerialOut::Write(uint8_t *data, uint64_t offset, uint64_t size)
{
	unsigned char *str = data;
	for(uint64_t i= 0; i < size; i++)
	{
		WriteChar(str[i]);
	}
	
	return size;
}
bool SerialOut::readyToTransmit()
{
	  uint8_t status = inb(m_port + 5);
	  return (bool) (status & 0x20);
}
void SerialOut::startColor()
{
	InternalWrite("\\e[");

	switch(m_color)
	{
		case CGA_COLOR_BLACK: 	 InternalWrite("0;30"); break;
		case CGA_COLOR_RED:  	 InternalWrite("0;31"); break;
		case CGA_COLOR_GREEN: 	 InternalWrite("0;32"); break;
		case CGA_COLOR_BROWN:	 InternalWrite("0;33"); break;
		case CGA_COLOR_BLUE:  	 InternalWrite("0;34"); break;
		case CGA_COLOR_MAGENTA:  InternalWrite("0;35"); break;
		case CGA_COLOR_CYAN: 	 InternalWrite("0;36"); break;
		case CGA_COLOR_LGREY:	 InternalWrite("0;37"); break;
		
		case CGA_COLOR_DGREY:	 InternalWrite("1;30"); break;
		case CGA_COLOR_PINK: 	 InternalWrite("1;31"); break;
		case CGA_COLOR_LGREEN:   InternalWrite("1;32"); break;
		case CGA_COLOR_YELLOW:   InternalWrite("1;33"); break;
		case CGA_COLOR_LBLUE:    InternalWrite("1;34"); break;
		case CGA_COLOR_LMAGENTA: InternalWrite("1;35"); break;
		case CGA_COLOR_LCYAN: 	 InternalWrite("1;36"); break;
		case CGA_COLOR_WHITE: 	 InternalWrite("1;37"); break;

		default: InternalWrite("1");
	};
 
	switch(m_bcolor)
	{
		case CGA_COLOR_BLACK: 	 InternalWrite("0;40"); break;
		case CGA_COLOR_RED:  	 InternalWrite("0;41"); break;
		case CGA_COLOR_GREEN: 	 InternalWrite("0;42"); break;
		case CGA_COLOR_BROWN:	 InternalWrite("0;43"); break;
		case CGA_COLOR_BLUE:  	 InternalWrite("0;44"); break;
		case CGA_COLOR_MAGENTA:  InternalWrite("0;45"); break;
		case CGA_COLOR_CYAN: 	 InternalWrite("0;46"); break;
		case CGA_COLOR_LGREY:	 InternalWrite("0;47"); break;

		case CGA_COLOR_DGREY:	 InternalWrite("1;40"); break;
		case CGA_COLOR_PINK: 	 InternalWrite("1;41"); break;
		case CGA_COLOR_LGREEN:   InternalWrite("1;42"); break;
		case CGA_COLOR_YELLOW:   InternalWrite("1;43"); break;
		case CGA_COLOR_LBLUE:    InternalWrite("1;44"); break;
		case CGA_COLOR_LMAGENTA: InternalWrite("1;45"); break;
		case CGA_COLOR_LCYAN: 	 InternalWrite("1;46"); break;
		case CGA_COLOR_WHITE: 	 InternalWrite("1;47"); break;
	}
  	InternalWrite("m");
}
void SerialOut::endColor()
{
	InternalWrite("\\e[0m");
}