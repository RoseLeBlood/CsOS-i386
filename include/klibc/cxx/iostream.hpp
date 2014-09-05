#ifndef _STD_IOSTREAM_H_
#define _STD_IOSTREAM_H_

#include <cxx/string.hpp>
#include <kernel/video.h>
#include <dev/Device.hpp>

namespace std
{
	
	namespace textcolor
	{
		enum textcolor_t
		{
			Black = CGA_COLOR_BLACK,
			Blue = CGA_COLOR_BLUE,
			Green = CGA_COLOR_GREEN,
			Cyan = CGA_COLOR_CYAN,
			Red = CGA_COLOR_RED,
			Magenta = CGA_COLOR_MAGENTA,
			Brown = CGA_COLOR_BROWN,
			LightGrey = CGA_COLOR_LGREY,
			DarkGrey= CGA_COLOR_DGREY,
			LightBlue = CGA_COLOR_LBLUE,
			LightGreen = CGA_COLOR_LGREEN,
			LightCyan = CGA_COLOR_LCYAN,
			Pink = CGA_COLOR_PINK,
			LightMagenta = CGA_COLOR_LMAGENTA,
			Yellow = CGA_COLOR_YELLOW,
			White = CGA_COLOR_WHITE
		};
	}
	namespace backcolor
	{
		enum backcolor_t
		{
			Black = CGA_COLOR_BLACK,
			Blue = CGA_COLOR_BLUE,
			Green = CGA_COLOR_GREEN,
			Cyan = CGA_COLOR_CYAN,
			Red = CGA_COLOR_RED,
			Magenta = CGA_COLOR_MAGENTA,
			Brown = CGA_COLOR_BROWN,
			LightGrey = CGA_COLOR_LGREY,
			DarkGrey= CGA_COLOR_DGREY,
			LightBlue = CGA_COLOR_LBLUE,
			LightGreen = CGA_COLOR_LGREEN,
			LightCyan = CGA_COLOR_LCYAN,
			Pink = CGA_COLOR_PINK,
			LightMagenta = CGA_COLOR_LMAGENTA,
			Yellow = CGA_COLOR_YELLOW,
			White = CGA_COLOR_WHITE
		};
	}
	
	// sehr einfach 
    class OStream 
	{
	public:
		OStream();
		OStream& operator <<(char *str);
		OStream& operator <<(const char *str);
		OStream& operator <<(char c);
		OStream& operator <<(unsigned char *str);
		OStream& operator <<(unsigned char c);
		OStream& operator <<(int i);
		OStream& operator <<(unsigned int i);
		OStream& operator <<(unsigned long i);
		OStream& operator <<(long double i);
		OStream& operator <<(std::basic_string<char> str);
		OStream& operator <<(std::basic_wstring<wchar_t> wstr);	
		
		OStream& operator <<(std::backcolor::backcolor_t cl);
		OStream& operator <<(std::textcolor::textcolor_t cl);
		OStream& operator <<(std::flags::flags_t cl)
		{
			current_flags = cl;
			return *this;
		}
		
		void flags(std::flags::flags_t f);
		std::flags::flags_t Getflags()		{ return current_flags; } 
		
		void SetDevice(const char* dev);
		void Clear();
	private:
		std::flags::flags_t current_flags;
	private:
		char	m_device[5];
		
	};
	
	
	class IStream
	{
		#define BUFFSIZE  256
	public:
		IStream();
		
		IStream& operator >> (char *cp);
		IStream& operator >> (char &c);
		IStream& operator >> (unsigned char *ucp);
		IStream& operator >> (unsigned char &uc);
		IStream& operator >> (unsigned int &i);
		char *getstring();
		char getChar();
		
		void SetDevice(const char* dev);
	private:
		unsigned int getString(bool hide = false);
	private:
		char	m_device[5];
		char buffer[BUFFSIZE];
	};
	
	
	
	const char endl = '\n';
	const char ends = '\0';
	const char tab  = '\t';
	
	extern OStream cout;  // kernel param -o
	extern OStream cerr;  // kernel param -e
	extern IStream cin;   // kernel param -i
} 

#endif 
