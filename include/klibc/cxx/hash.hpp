#ifndef _STD_HASH_H_
#define _STD_HASH_H_

namespace std
{
	typedef unsigned long   hash_value_t;
    
	template<typename T> hash_value_t extracthashkey(const T& t) //extract_int_key_value
	{
        return (hash_value_t)t;
	}
 
	template<typename T> struct hash
	{
        hash_value_t operator()(const T& t) const
        {
            hash_value_t a = extracthashkey(t);
	        a = (a+0x7ed55d16) + (a<<12);
	        a = (a^0xc761c23c) ^ (a>>19);
	        a = (a+0x165667b1) + (a<<5);
	        a = (a+0xd3a2646c) ^ (a<<9);
	        a = (a+0xfd7046c5) + (a<<3);
	        a = (a^0xb55a4f09) ^ (a>>16);
	        return a;
        }
	};
}

#endif
