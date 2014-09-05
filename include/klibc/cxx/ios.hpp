#ifndef _STD_IOS_HPP_
#define _STD_IOS_HPP_

#include <cxx/common.hpp>
#include <cxx/utility.hpp>
#include <cxx/string.hpp>

#include <cxx/streambuf.hpp>

extern "C"
{
   #include <stdio.h>
}
namespace std
{
	template<typename _char_t, typename _traits_t> class basic_ios
	{
	public:
    	typedef _char_t     char_type;

   	protected:
    	basic_streambuf<_char_t, _traits_t>*     _m_streambuf;

   	public:
       	basic_streambuf<_char_t, _traits_t>* rdbuf()
        {
        	return _m_streambuf;
        }
   	protected:
        void init(basic_streambuf<_char_t, _traits_t>* _streambuf) 
        {
        	_m_streambuf = _streambuf;
        }
	};
	
	
	template<typename _char_t, typename _traits_t> class basic_ostream;
	typedef basic_ostream<char, char> ostream;
	
	template<typename _char_t, typename _traits_t> class basic_ostream : virtual public basic_ios<_char_t, _traits_t>
	{
	public:
        typedef char char_type;
        
        typedef basic_ostream<_char_t, _traits_t> _current_ostream_t;

        explicit basic_ostream(basic_streambuf<_char_t, _traits_t>* streambuf)
        {
            this->init(streambuf);
        }
        _current_ostream_t& put(char_type c)
        {
            if(this->rdbuf())
            {
                this->rdbuf()->sputc(c);
            }

            return *this;
        }
        _current_ostream_t& write(const char_type* str, streamsize size)
        {
            if(this->rdbuf())
            {
                this->rdbuf()->sputn(str, size);
            }

            return *this; 
        }
        _current_ostream_t& flush()
        {
            if(this->rdbuf())
            {
                this->rdbuf()->pubsync();
            }
            return *this;
        }
        _current_ostream_t& operator<<(unsigned int number)
        {
            char str[256];

            sprintf(str, "%u", number);
            write(str, strlen(str));
            delete str;

            return *this;
        }
        _current_ostream_t& operator<<(signed int number)
        {
            char str[256];
            
            sprintf(str, "%d", number);
            write(str, strlen(str));
            delete str;

            return *this;
        }
        _current_ostream_t& operator<< (_current_ostream_t& (*pf)(_current_ostream_t&))
        {
            return pf(*this);
        }
	};
	ostream& operator<< (ostream& out, const char* s);
    
    template<typename _char_t, typename _traits_t>
    basic_ostream<_char_t, _traits_t>& endl(basic_ostream<_char_t, _traits_t>& out)
    {
        out.put('\n');
        out.flush();
        return out;
    }
	template<typename _char_t, typename _traits_t>
    basic_ostream<_char_t, _traits_t>& ends(basic_ostream<_char_t, _traits_t>& out)
    {
        out.put('\0');
        out.flush();
        return out;
    }
}
#endif