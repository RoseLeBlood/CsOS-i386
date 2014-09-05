#ifndef _STD_ALIGNMENT_H_
#define _STD_ALIGNMENT_H_

#include "common.hpp"
#include <stddef.h>

namespace std
{
	namespace internal
	{
	#pragma warning(push)

	        template<typename T>
	        struct alignof_helper
	        {
	                char    x;
	                T 		y;
	        };

	    struct __attribute__ ((aligned (16))) aligned16 { uint64 member[2]; } ;
	    
	#pragma warning(pop)
	        template<size_t N> struct type_with_alignment
	        {
	                typedef char err_invalid_alignment[N > 0 ? -1 : 1];
	        };
	        template<> struct type_with_alignment<0> {};
	        template<> struct type_with_alignment<1> { uint8 member; };
	        template<> struct type_with_alignment<2> { uint16 member; };
	        template<> struct type_with_alignment<4> { uint32 member; };
	        template<> struct type_with_alignment<8> { uint64 member; };
	        template<> struct type_with_alignment<16> { aligned16 member; };
	}
	template<typename T>
	struct alignof
	{
	        enum 
	        {
	                res = offsetof(internal::alignof_helper<T>, y)
	        };
	};
	template<typename T>
	struct aligned_as
	{
	        typedef typename internal::type_with_alignment<alignof<T>::res> res;
	};

}

#endif
