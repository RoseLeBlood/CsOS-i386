#ifndef _STD_STRING_H_

#define _STD_STRING_H_
#define _STD_WSTRING_H_

#include <cxx/basic_string.hpp>
#include <cxx/hash.hpp>
#include <cxx/basic_wstring.hpp>

namespace std
{
	typedef basic_string<char> string;
	typedef basic_wstring<wchar_t> wstring;
	
	
	template<typename E, class TAllocator, typename TStorage>
	struct hash<basic_string<E, TAllocator, TStorage> >
	{
	    hash_value_t operator()(const basic_string<E, TAllocator, TStorage>& x) const 
	    {
	        hash_value_t h = 0;
	        for (typename basic_string<E, TAllocator, TStorage>::size_type p = 0; p < x.length(); ++p) 
	        {
	            h = x[p] + (h<<6) + (h<<16) - h;
	        }
	        return h & 0x7FFFFFFF;
	    }
	};
	
	template<typename E, class TAllocator, typename TStorage>
	struct hash<basic_wstring<E, TAllocator, TStorage> >
	{
	    hash_value_t operator()(const basic_wstring<E, TAllocator, TStorage>& x) const 
	    {
	        hash_value_t h = 0;
	        for (typename basic_wstring<E, TAllocator, TStorage>::size_type p = 0; p < x.length(); ++p) 
	        {
	            h = x[p] + (h<<6) + (h<<16) - h;
	        }
	        return h & 0x7FFFFFFF;
	    }
	};
	inline basic_string<char>	StringFromWString(basic_wstring<wchar_t> string)
	{
		char buf[wcslen(string.c_str() - 1)];
		wcstombs(buf, string.c_str(), wcslen(string.c_str() - 1));
	
		return basic_string<char>(buf);
	}
}

#endif 
