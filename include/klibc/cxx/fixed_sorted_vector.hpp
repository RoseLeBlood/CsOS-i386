#ifndef _STD_FIXED_SORTED_VECTOR_H_
#define _STD_FIXED_SORTED_VECTOR_H_

#include <cxx/fixed_vector.hpp>
#include <cxx/sorted_vector.hpp>

namespace std
{
	template<typename TKey, typename TValue,  int TCapacity, bool TGrowOnOverflow, class TCompare = std::less<TKey>, class TAllocator = std::allocator>
		class fixed_sorted_vector : public sorted_vector<TKey, TValue, TCompare, TAllocator, fixed_vector_storage<pair<TKey, TValue>, TAllocator, TCapacity, TGrowOnOverflow> >
	{
	public:
		explicit fixed_sorted_vector(const allocator_type& allocator = allocator_type())
			: sorted_vector(allocator)
		{
		}
	};
}


#endif 
