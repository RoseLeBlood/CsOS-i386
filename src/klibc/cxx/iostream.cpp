#include <klibc/cxx/iostream.hpp>
#include <kernel/kernel.hpp>
#include <stdio.h>
#include <dev/key_input.hpp>


extern "C" void putchar	(const char c)
{
	std::cout << c;
	
}
extern "C" void puts(const char *c)
{
	std::cout << c;
}
extern "C" void cls()
{
	std::cout.Clear();
}
extern "C" void setBackColor(uint8_t back)
{
	std::cout << (std::backcolor::backcolor_t)(back);
}
extern "C" void setFrontColor(uint8_t front)
{
	std::cout << (std::textcolor::textcolor_t)(front);
}

extern "C" int SetTextColorStream(void* stream, uint16_t color);
extern "C" int SetBackColorStream(void* stream, uint16_t color);
/* getch */
extern "C" int getch()
{       
    return std::cin.getChar();
}
namespace std
{
	OStream cout; 
	IStream cin;
	
	OStream::OStream()
	{
		current_flags = flags::dec;
	}
	OStream& OStream::operator <<(char *str)
	{
		WriteStream(GetDeviceByName(m_device), (uint8_t*)str, 0, strlen(str));

		return *this;
	}
	OStream& OStream::operator <<(const char *str)
	{
		char text[260] = "";
		strcpy(text, str);
		
		WriteStream(GetDeviceByName(m_device), (uint8_t*)str, 0, strlen(str));

		return *this;
	}
	OStream& OStream::operator <<(char c)
	{
		if(current_flags & flags::hex)
		{
			char buf[3];
			_itoa(buf, 16, c);

			WriteStream(GetDeviceByName(m_device), (uint8_t*)buf, 0, strlen(buf));
			//((dev::IOutDeviceStream*)dev)->Write((uint8_t*)buf, 0, strlen(buf));
		}
		else
		 {
			//dev::Driver* dev = ((Kernel*)kernel_instance)->GetDriver(m_device);
			//((dev::IOutDeviceStream*)dev)->WriteChar(c);
			WriteCharStream(GetDeviceByName(m_device), c);
		 }
		return *this;
	}

	OStream& OStream::operator <<(unsigned char *str)
	{
		//dev::Driver* dev = ((Kernel*)kernel_instance)->GetDriver(m_device);
		//((dev::IOutDeviceStream*)dev)->Write((uint8_t*)str, 0, strlen(str));
		WriteStream(GetDeviceByName(m_device), (uint8_t*)str, 0, strlen(str));
		return *this;
	}

	OStream& OStream::operator <<(unsigned char c)
	{
		//dev::Driver* dev = ((Kernel*)kernel_instance)->GetDriver(m_device);
		WriteCharStream(GetDeviceByName(m_device), c);
		return *this;
	}

	OStream& OStream::operator <<(int i)
	{
		char buf[256];
		
		if (current_flags & flags::dec)
			sprintf(buf, "%d", i);
		else if (current_flags & flags::hex && current_flags & flags::showbase)
			sprintf(buf, "0x%X", i);
		else if (current_flags & flags::hex)
			sprintf(buf, "%X", i);
		else if (current_flags & flags::oct)
			_itoa(buf, 8, i);
		else if (current_flags & flags::bin)
			sprintf(buf, "%b", i);
		else
			sprintf(buf, "%d", i);

		WriteStream(GetDeviceByName(m_device), (uint8_t*)buf, 0, strlen(buf));
		return *this;
	}

	OStream& OStream::operator <<(unsigned int i)
	{
		char buf[256];
		
		if (current_flags & flags::dec)
			sprintf(buf, "%d", i);
		else if (current_flags & flags::hex && current_flags & flags::showbase)
			sprintf(buf, "0x%X", i);
		else if (current_flags & flags::hex)
			sprintf(buf, "%X", i);
		else if (current_flags & flags::oct)
			_itoa(buf, 8, i);
		else if (current_flags & flags::bin)
			sprintf(buf, "%b", i);
		else
			sprintf(buf, "%d", i);


		//dev::Driver* dev = ((Kernel*)kernel_instance)->GetDriver(m_device);
		//((dev::IOutDeviceStream*)dev)->Write((uint8_t*)buf, 0, strlen(buf));
		WriteStream(GetDeviceByName(m_device), (uint8_t*)buf, 0, strlen(buf));
		return *this;
	}
	OStream& OStream::operator <<(unsigned long i)
	{
		char buf[256];
		
		if (current_flags & flags::dec)
			sprintf(buf, "%d", i);
		else if (current_flags & flags::hex && current_flags & flags::showbase)
			sprintf(buf, "0x%X", i);
		else if (current_flags & flags::hex)
			sprintf(buf, "%X", i);
		else if (current_flags & flags::oct)
			_itoa(buf, 8, i);
		else if (current_flags & flags::bin)
			sprintf(buf, "%b", i);
		else
			sprintf(buf, "%d", i);


		//dev::Driver* dev = ((Kernel*)kernel_instance)->GetDriver(m_device);
		//((dev::IOutDeviceStream*)dev)->Write((uint8_t*)buf, 0, strlen(buf));
		WriteStream(GetDeviceByName(m_device), (uint8_t*)buf, 0, strlen(buf));
		return *this;
	}
	OStream& OStream::operator <<(long double i)
	{
		char buf[256];
		
		if (current_flags & flags::dec)
			sprintf(buf, "%d", i);
		else if (current_flags & flags::hex && current_flags & flags::showbase)
			sprintf(buf, "0x%X", i);
		else if (current_flags & flags::hex)
			sprintf(buf, "%X", i);
		else if (current_flags & flags::oct)
			_itoa(buf, 8, i);
		else if (current_flags & flags::bin)
			sprintf(buf, "%b", i);
		else
			sprintf(buf, "%d", i);


		//dev::Driver* dev = ((Kernel*)kernel_instance)->GetDriver(m_device);
		//((dev::IOutDeviceStream*)dev)->Write((uint8_t*)buf, 0, strlen(buf));
		WriteStream(GetDeviceByName(m_device), (uint8_t*)buf, 0, strlen(buf));
		return *this;
	}
	void OStream::flags(std::flags::flags_t f)
	{
		current_flags = f;
	}
	OStream& OStream::operator << (std::basic_string<char> str)
	{
		*this << str.c_str();
		return *this;
	}
	OStream& OStream::operator <<(std::basic_wstring<wchar_t> wstr)
	{
		*this  << std::StringFromWString(wstr);
		return *this;
	}
		
	OStream& OStream::operator <<(std::backcolor::backcolor_t cl)
	{
		//BackColor
		dev::Driver* dev = ((Kernel*)kernel_instance)->GetDriver(m_device);
		dev->BackColor(cl);
		return *this;
	}
	OStream& OStream::operator <<(std::textcolor::textcolor_t cl)
	{

		dev::Driver* dev = ((Kernel*)kernel_instance)->GetDriver(m_device);
		dev->TextColor(cl);
		return *this;
	}
	void OStream::SetDevice(const char* dev)
	{
		strcpy(m_device, dev);
	}
	void OStream::Clear()
	{
		dev::Driver* dev = ((Kernel*)kernel_instance)->GetDriver(m_device);
		dev->Clear();
	}
	
	
	
	inline void getWord(char *str1, char *p1)
	{						

		if(*str1 != '\0')
		{
			while(*str1 != ' ')
			{
				if(*str1 == '\0')
				{ 
					*p1 = '\0';
					break;
				}
				*p1 = *str1;
				*p1++;
				*str1++;
			}
		}
		else
		{
			*p1 = '\0';
		}
	}
	IStream::IStream()
	{
		strcpy(m_device, "kb0");
	}	
	IStream& IStream::operator >> (char *cp)
	{
		getWord(getstring(), cp);
		return *this;
	}
	IStream& IStream::operator >> (char &c)
	{
		
		c = getstring()[0];
		
		return *this;
	}
	IStream& IStream::operator >> (unsigned char *ucp)
	{
		getWord(getstring(), (char*) ucp);
		return *this;
	}
	IStream& IStream::operator >> (unsigned char &uc)
	{
		uc = getstring()[0];
		return *this;
	}
	IStream& IStream::operator >> (unsigned int &i)
	{
		//dev::Driver* dev = ((Kernel*)kernel_instance)->GetDriver(m_device);
		i = atoi(getstring());
		return *this;
	}
	unsigned int IStream::getString(bool hide)
	{						
		char input = '\0';	
		unsigned int control = 0;

		while(1)
		{
			input = getChar();


			if((input == '\r') || (input == '\n'))
			{
				if(control >= (BUFFSIZE - 2))
				{
					control++;
				}
				buffer[control] = '\0';

				return control;
			}
			else if((input == 8) && (control > 0))
			{
				control--;
				if(!hide) cout << (input);
			}
			else if(input >= ' ')
			{
				buffer[control] = input;
				if(control < (BUFFSIZE - 2))
				{
					control++;
				}
				else
				{
					if(!hide) cout << ((char)8);
				}
				if(!hide) cout << (input);
			}
		}
	}
	
	char *IStream::getstring()
	{
		getString(false);
		return buffer;
	}
	char IStream::getChar()
	{
		return ReadCharStream(GetDeviceByName(m_device));
	}
	void IStream::SetDevice(const char* dev)
	{
		strcpy(m_device, dev);
	}
}
