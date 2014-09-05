#ifndef _STD_STRINGSTREAM_H_
#define _STD_STRINGSTREAM_H_

#include <cxx/common.hpp>
#include <cxx/string.hpp>
#include <cxx/vector.hpp>
#include <string.h>

namespace std 
{
    template< typename E, typename TAlloc = std::allocator > struct basic_stringstream
    {
        typedef E                                   value_type;
        typedef std::vector<value_type, TAlloc>     buffer_type;
        typedef typename buffer_type::size_type     size_type;
        typedef basic_string<value_type, TAlloc>	string_type;
        
        explicit basic_stringstream(const value_type* inp) 
        { 
        	init(inp); 
        }
        explicit basic_stringstream(const string_type& inp) 
        { 
        	init(inp.c_str()); 
        }

        basic_stringstream() 
        {
        
        }
 
        bool good() const 
        { 
        	return buffer.size() ? cursor != buffer.end() : false; 
        }
        bool eof() const 
        { 
        	return !good(); 
        }
        operator bool() const 
        { 
        	return good(); 
        }
        
        void reset(const value_type* inp) 
        {
            init(inp);
        }
        string_type str()
        {
        	string_type	strr = string_type();
        	
        	while(next())
        	{
        		strr.append(current);
        	}
        	return strr;
        }
        //------------------------------------------------------
        //Output operators
        basic_stringstream& operator>>(int& x) 
        {
	        if( next() ) 
	            x = atoi((const char*)current.c_str());
	        return *this;
        }
        basic_stringstream& operator>>(long& x) 
        {
            if( next() ) 
                x = atol((const char*)current.c_str());
            return *this;
        }
        basic_stringstream& operator>>(float& x) 
        {
            if( next() ) 
                x = atof((const char*)current.c_str());
            return *this;
        }
        basic_stringstream& operator>>(std::string& x) 
        {
            if( next() ) 
                x = current;
            return *this;
        }        
    private:
        void init(const value_type* inp) 
        {
            if( !inp || !strlen(inp) ) 
            {
                cursor = buffer.end();
                return;
            }
            const size_type len = strlen(inp);
            buffer.resize(len);
            memmove(buffer.begin(), inp, len);
            cursor = buffer.begin();
            current.clear();
            ltrim();
        }
        
        bool is_whitespace(const value_type& ch) const 
        {
            return (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n');
        }
        
        void ltrim() 
        {
            while(is_whitespace(*cursor)) 
                ++cursor;
        }
        
        bool next() 
        {
            if(!buffer.size())
                return false;
            current.clear();
            for(; cursor!=buffer.end(); ++cursor) 
            {
                if(!is_whitespace(*cursor)) 
                {
                    current.append(*cursor);   
                } else 
                {
                    ltrim();
                    break;
                }
            }
            return current.length();
        }
        
        string_type 						 current;
        buffer_type 						 buffer;
        typename buffer_type::const_iterator cursor;
    };    
    typedef basic_stringstream<char> stringstream;
}


#endif
