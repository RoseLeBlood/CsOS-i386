#ifndef __DEV_SERIAL_OUT_HPP__
#define __DEV_SERIAL_OUT_HPP__

#include <dev/Driver.hpp>
#include <iob.h>

namespace dev
{
	// 8 bits, no parity, one stop bit
	class SerialOut : public Driver
	{
	public:
		SerialOut(int port) ;

		virtual bool Probe();
		
		virtual char ReadChar() { return ' '; }
		virtual void WriteChar(char c);
		virtual void Write(const char* c);
		virtual void GotoXY(unsigned short x, unsigned short y);
		virtual void Clear();
		
		virtual void TextColor(uint16_t color);
		virtual void BackColor(uint16_t color);
		
		virtual uint64_t Read(uint8_t *data, uint64_t offset, uint64_t size);
		virtual uint64_t Write(uint8_t *data, uint64_t offset, uint64_t size);
		
		int getPort() { return m_port; }
	protected:
		bool readyToTransmit();
		
		void startColor();
		void endColor();
	private:
		void InternalWrite(const char* c);
	protected:
		int m_port;
		int m_irq;
		uint16_t m_bcolor;
	};
}
#endif
