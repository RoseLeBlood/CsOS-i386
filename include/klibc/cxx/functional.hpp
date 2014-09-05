#ifndef _STD_FUNCTIONAL_H_
#define _STD_FUNCTIONAL_H_

namespace std
{
	template<typename T> struct less
	{
	        bool operator()(const T& lhs, const T& rhs) const
	        {
	                return lhs < rhs;
	        }
	};
	template<typename T> struct greater
	{
	        bool operator()(const T& lhs, const T& rhs) const
	        {
	                return lhs > rhs;
	        }
	};
	template<typename T> struct equal_to
	{
	        bool operator()(const T& lhs, const T& rhs) const
	        {
	                return lhs == rhs;
	        }
	};
}
#endif 
