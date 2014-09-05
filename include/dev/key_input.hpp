#ifndef __DEV_KEY_INPUT_HPP__
#define __DEV_KEY_INPUT_HPP__

#include <dev/Driver.hpp>

#define KB_CMD_PORT 0x64
#define KB_DATA_PORT 0x60
#define KB_ACK_PORT 0x61

#define CAPS_LED 4
#define NUM_LED 2
#define SCROLL_LED 1

#define LEFT_SHIFT  0x01
#define RIGHT_SHIFT 0x02
#define LEFT_CTRL   0x04
#define RIGHT_CTRL  0x08
#define LEFT_ALT    0x10
#define RIGHT_ALT   0x20
#define SHIFT_MASK  (LEFT_SHIFT | RIGHT_SHIFT)
#define CTRL_MASK   (LEFT_CTRL | RIGHT_CTRL)
#define ALT_MASK    (LEFT_ALT | RIGHT_ALT)

#define KB_OUTPUT_FULL 0x01
#define KB_KEY_RELEASE 0x80




#define KEY_SPECIAL_FLAG 0x0100
#define KEY_KEYPAD_FLAG  0x0200
#define KEY_SHIFT_FLAG   0x1000
#define KEY_ALT_FLAG     0x2000
#define KEY_CTRL_FLAG    0x4000
#define KEY_RELEASE_FLAG 0x8000


#define _SPECIAL(num) (KEY_SPECIAL_FLAG | (num))
#define KEY_UNKNOWN _SPECIAL(0)
#define KEY_F1      _SPECIAL(1)
#define KEY_F2      _SPECIAL(2)
#define KEY_F3      _SPECIAL(3)
#define KEY_F4      _SPECIAL(4)
#define KEY_F5      _SPECIAL(5)
#define KEY_F6      _SPECIAL(6)
#define KEY_F7      _SPECIAL(7)
#define KEY_F8      _SPECIAL(8)
#define KEY_F9      _SPECIAL(9)
#define KEY_F10     _SPECIAL(10)
#define KEY_F11     _SPECIAL(11)
#define KEY_F12     _SPECIAL(12)
#define KEY_LCTRL   _SPECIAL(13)
#define KEY_RCTRL   _SPECIAL(14)
#define KEY_LSHIFT  _SPECIAL(15)
#define KEY_RSHIFT  _SPECIAL(16)
#define KEY_LALT    _SPECIAL(17)
#define KEY_RALT    _SPECIAL(18)
#define KEY_PRINTSCRN _SPECIAL(19)
#define KEY_CAPSLOCK _SPECIAL(20)
#define KEY_NUMLOCK _SPECIAL(21)
#define KEY_SCRLOCK _SPECIAL(22)
#define KEY_SYSREQ  _SPECIAL(23)


#define KEYPAD_START 128
#define _KEYPAD(num) (KEY_KEYPAD_FLAG | KEY_SPECIAL_FLAG | (num+KEYPAD_START))
#define KEY_KPHOME  _KEYPAD(0)
#define KEY_KPUP    _KEYPAD(1)
#define KEY_KPPGUP  _KEYPAD(2)
#define KEY_KPMINUS _KEYPAD(3)
#define KEY_KPLEFT  _KEYPAD(4)
#define KEY_KPCENTER _KEYPAD(5)
#define KEY_KPRIGHT _KEYPAD(6)
#define KEY_KPPLUS  _KEYPAD(7)
#define KEY_KPEND   _KEYPAD(8)
#define KEY_KPDOWN  _KEYPAD(9)
#define KEY_KPPGDN  _KEYPAD(10)
#define KEY_KPINSERT _KEYPAD(11)
#define KEY_KPDEL   _KEYPAD(12)


#define ASCII_ESC 0x1B
#define ASCII_BS  0x08

namespace dev
{
	class StdKeyboard : public Driver
	{
	public:
		StdKeyboard() : Driver("Kayboard", "kb", 0,0, 0x07, false, true) { }
		~StdKeyboard() { }

		virtual bool Probe();
		
		virtual uint64_t Read(uint8_t *data, uint64_t offset, uint64_t size);
		virtual uint64_t Write(uint8_t *data, uint64_t offset, uint64_t size);

		virtual char ReadChar();
		
		virtual void setLeds(uint8_t leds);
	protected:
		virtual void callback(registers_t *reg);
	public:
		virtual void Wait();
		
		virtual void flush();
		virtual void SendData(unsigned char data); 
		virtual void SendCommand(unsigned char c);	
	private:
		unsigned short sKey();
	private:
		int 			m_shift;
		int 			m_ctrl;
		int 			m_alt;
		int 			m_capslock;
		unsigned char 	m_buffer[129];
		int 			buffend;
	};
}
#endif
