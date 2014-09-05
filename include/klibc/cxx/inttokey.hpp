#ifndef _STD_INT_TO_TYPE_H_
#define _STD_INT_TO_TYPE_H_

namespace std
{
	template<int TVal> struct int_to_type
	{
	    enum 
	    {
	        value = TVal
	    };
	};

} 

#endif 	
