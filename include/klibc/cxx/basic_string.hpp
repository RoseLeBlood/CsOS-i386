#ifndef _STD_BASIC_STRING_H_
#define _STD_BASIC_STRING_H_

#include <cxx/allocator.hpp>
#include <cxx/common.hpp>
#include <cxx/simple_string_storage.hpp>
#include <cxx/string_utils.hpp>
#include <stdio.h>

namespace std
{
	namespace flags
	{
		enum flags_t
		{
			 boolalpha =	0x0001,
			 showbase  =	0x0002,
			 showpoint =	0x0004,
			 showpos =		0x0008,
			 skipws =		0x0010,
			 unitbuf =		0x0020, 
			 uppercase =	0x0040, 
			 dec =			0x0080,
			 hex =			0x0100,
			 oct =			0x0200,
			 bin =			0x0400,
			 internal =		0x0800, 
			 left =			0x1000, 
			 right =		0x2000, 
			 
			 hexbase = 		hex | showbase
		};
	}
	
	template<typename E, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
	class basic_string : private TStorage
	{
	public:
		typedef typename TStorage::value_type           value_type;
		typedef typename TStorage::size_type            size_type;
		typedef typename TStorage::const_iterator       const_iterator;
		typedef typename TStorage::allocator_type       allocator_type;

		//For find
		static const size_type npos = size_type(-1);

		explicit basic_string(const allocator_type& allocator = allocator_type())
			: TStorage(allocator)
		{
		        /**/
		}
		explicit basic_string(const value_type* str, const allocator_type& allocator = allocator_type())
			: TStorage(str, allocator)
		{
		        /**/
		}
		basic_string(const value_type* str, size_type len, const allocator_type& allocator = allocator_type())
			: TStorage(str, len, allocator)
		{
		        /**/
		}
		basic_string(const basic_string& str, const allocator_type& allocator = allocator_type())
		 	: TStorage(str, allocator)
		{
		        /**/
		}
		~basic_string()
		{
		        /**/
		}

		size_type capacity() const 
		{ 
			return TStorage::capacity(); 
		}
		basic_string& operator <<(const value_type* str)
		{
			append(str, strlen(str));
			return *this;
		}
		basic_string& operator <<(const value_type ch)
		{
			append(&ch, 1);
			return *this;
		}
		basic_string& operator <<(const basic_string& str)
		{
			append(str.c_str(), str.length());
			return *this;
		}
		basic_string& operator <<(std::flags::flags_t cl)
		{
			current_flags = cl;
			return *this;
		}
		basic_string& operator <<(int i)
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
			
			append(buf, 256);
			
			return *this;
		}
		basic_string& operator <<(unsigned int i)
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
			
			append(buf, 256);
			
			return *this;
		}
		basic_string& operator <<(unsigned long i)
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
			
			append(buf, 256);
			return *this;
		}
		basic_string& operator <<(long double i)
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
			
			append(buf, 256);
			return *this;
		}
		
		value_type operator[](size_type i) const
		{
	        assert(i < length());
	        assert(invariant());
	        return c_str()[i];
		}
		
		basic_string& operator=(const basic_string& rhs)
		{
	        assert(rhs.invariant());
	        if (this != &rhs) 
	        {
	    		TStorage::operator=((TStorage&)rhs);
	        }
	        assert(invariant());
	        return *this;
		}
		basic_string& operator=(const value_type* str)
		{
	        return assign(str);
		}
		basic_string& assign(const value_type* str, size_type len)
		{
	        TStorage::assign(str, len);
	        assert(invariant());
	        return *this;
		}
		basic_string& assign(const value_type* str)
		{
	        return assign(str, strlen(str));
		}

		basic_string substr(size_type begin, size_type end) const
		{
	        assert(end >= begin && end <= length() && begin >= 0);
	        return basic_string(c_str() + begin, end - begin);
		}
		basic_string substr(size_type begin) const
		{
			return substr(begin, length());
		}

		void append(const value_type* str, size_type len)
		{
			if( !str || len == 0 || *str == 0 )
		    	return;
		   	TStorage::append(str, len);
		}
		void append(const basic_string& str)
		{
			append(str.c_str(), str.length());
		}
		void append(const value_type* str)
		{
			append(str, strlen(str));
		}
		void append(const value_type ch)
		{
			append(&ch, 1);
		}
		basic_string& operator+=(const basic_string& rhs)
		{
	        append(rhs);
	        return *this;
		}

		int compare(const value_type* str) const
		{
	        const size_type thisLen = length();
	        const size_type strLen = strlen(str);
	        if (thisLen < strLen)
	                return -1;
	        if (thisLen > strLen)
	                return 1;

	        return strcompare(c_str(), str, thisLen);
		}
		int compare(const basic_string& rhs) const
		{
	        const size_type thisLen = length();
	        const size_type rhsLen = rhs.length();
	        if (thisLen < rhsLen)
	                return -1;
	        if (thisLen > rhsLen)
	                return 1;

	        return strcompare(c_str(), rhs.c_str(), thisLen);
		}

		const value_type* c_str() const
		{
	        assert(invariant());
	        return TStorage::c_str();
		}
		const_iterator begin() const    
		{ 
			assert(invariant()); return c_str(); 
		}
		const_iterator end() const             
		{ 
			assert(invariant()); return c_str() + length(); 
		}

		size_type length() const
		{
		        return TStorage::length();
		}
		bool empty() const      
		{ 
			return length() == 0; 
		}

		const allocator_type& get_allocator() const    
		{ 
			return TStorage::get_allocator; 
		}

		value_type* reserve(size_type capacity_hint)
		{
		        return TStorage::reserve(capacity_hint);
		}
		void clear()
		{
		        TStorage::clear();
		}
		void resize(size_type size)
		{
		        TStorage::resize(size);
		}
		void make_lower()
		{
	        const size_type len = length();
	        TStorage::make_unique(len);
	        static const int chDelta = 'a' - 'A';
	        E* data = TStorage::get_data();
	        for (size_type i = 0; i < len; ++i)
	        {
	                if (data[i] < 'a')
	                        data[i] += chDelta;             
	        }
		}
		void make_upper()
		{
	        const size_type len = length();
	        TStorage::make_unique(len);
	        static const int chDelta = 'a' - 'A';
	        E* data = TStorage::get_data();
	        for (size_type i = 0; i < len; ++i)
	        {
	                if (data[i] > 'Z')
	                        data[i] -= chDelta;
	        }
		}

		size_type find_index_of(const value_type ch) const
		{
		    size_type retIndex(basic_string::npos);
	        const E* ptr = c_str();
	        size_type currentIndex(0);
	        while (*ptr != value_type(0))
	        {
	                if (*ptr == ch)
	                {
	                        retIndex = currentIndex;
	                        break;
	                }
	                ++ptr;
	                ++currentIndex;
	        }
	        return retIndex;
		}
		size_type find_index_of_last(const value_type ch) const
		{
	        size_type retIndex(basic_string::npos);
	        const value_type* ptr = c_str();
	        size_type currentIndex(0);
	        while (*ptr != value_type(0))
	        {
	                if (*ptr == ch)
	                        retIndex = currentIndex;
	                ++ptr;
	                ++currentIndex;
	        }
	        return retIndex;
		}

		size_type find(const value_type* needle) const
		{       
			const value_type* s(c_str());    
			size_type si(0);
			while(*s)
			{
			    const value_type* n = needle;
			    if( *s == *n ) //first character matches
			    {
			        //go through the sequence, and make sure while(x) x == n for all of n
			        const value_type* x = s; 
			        size_type match = 0;
			        while(*x && *n) 
			        {
			            if( *n == *x )
			                ++match;
			            ++n;
			            ++x;
			        }
			        if( match == strlen(needle) )
			            return si;
			    }
			    ++s;
			    ++si;
			}
			return basic_string::npos;
		}

		size_type rfind(const value_type* needle) const
		{   
	        const value_type* s(c_str() + length());
	        size_type si(length()+1); 

	        while(--si >= 0) 
	        {
	                if( *s-- == *needle ) 
	                {
	                        const value_type* x = c_str() + si; 
	                        const value_type* n = needle;
	                        size_type match = 0;
	                        while(*x && *n) 
	                        {
	                                if( *n == *x )
	                                        ++match;
	                                ++n;
	                                ++x;
	                        }
	                        if( match == strlen(needle) )
	                                return si;
	                }
	        }
	        return basic_string::npos;
		}

	private:
		bool invariant() const
		{
		        return TStorage::invariant();
		}
		std::flags::flags_t current_flags;
	};

	template<typename E, class TStorage, class TAllocator>
	bool operator==(const basic_string<E, TStorage, TAllocator>& lhs, const basic_string<E, TStorage, TAllocator>& rhs)
	{
	        return lhs.compare(rhs) == 0;
	}
	template<typename E, class TStorage, class TAllocator>
	bool operator!=(const basic_string<E, TStorage, TAllocator>& lhs,  const basic_string<E, TStorage, TAllocator>& rhs)
	{
	        return !(lhs == rhs);
	}

	template<typename E, class TStorage, class TAllocator>
	bool operator<(const basic_string<E, TStorage, TAllocator>& lhs,  const basic_string<E, TStorage, TAllocator>& rhs)
	{
	        return lhs.compare(rhs) < 0;
	}

	template<typename E, class TStorage, class TAllocator>
	bool operator>(const basic_string<E, TStorage, TAllocator>& lhs,  const basic_string<E, TStorage, TAllocator>& rhs)
	{
	        return lhs.compare(rhs) > 0;
	}
}  
#endif
