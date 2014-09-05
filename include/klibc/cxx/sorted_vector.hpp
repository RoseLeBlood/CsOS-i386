#ifndef STD_SORTED_VECTOR_H
#define STD_SORTED_VECTOR_H

#include <cxx/functional.hpp>
#include <cxx/pair.hpp>
#include <cxx/sort.hpp>
#include <cxx/vector.hpp>

namespace std
{
	namespace internal
	{
	    template<class TPair, class TFunctor>
	    struct compare_func
	    {
	        bool operator()(const TPair& lhs, const TPair& rhs) const
	        {
	                return TFunctor()(lhs.first, rhs.first);
	        }
	        bool operator()(const TPair& lhs, const typename TPair::first_type& rhs) const
	        {
	                return TFunctor()(lhs.first, rhs);
	        }
	        bool operator()(const typename TPair::first_type& lhs, const TPair& rhs) const
	        {
	                return TFunctor()(lhs, rhs.first);
	        }
	    };
	}

	template<typename TKey, typename TValue, class TCompare = std::less<TKey>, class TAllocator = std::allocator, 
        class TStorage = std::standard_vector_storage<pair<TKey, TValue>, TAllocator> >
	class sorted_vector : private vector<pair<TKey, TValue>, TAllocator, TStorage >
	{
        typedef vector<pair<TKey, TValue>, TAllocator, TStorage>        Base;
	public:
        typedef TKey                                                    key_type;
        typedef TValue                                                  mapped_type;
        typedef typename Base::size_type                				size_type;
        typedef typename Base::value_type               				value_type;
        typedef typename Base::iterator                 				iterator;
        typedef typename Base::const_iterator   						const_iterator;
        typedef typename Base::allocator_type   						allocator_type;

        explicit sorted_vector(const allocator_type& allocator = allocator_type())
        	: Base(allocator)
        {
        }
        template <class InputIterator> sorted_vector(InputIterator first, InputIterator last, 
                const allocator_type& allocator = allocator_type())
        	: Base(first, last, allocator)
        {
         	std::quick_sort(begin(), end(), m_compare);
         	assert(invariant());
        }
        using Base::begin;
        using Base::end;
        using Base::size;
        using Base::empty;
        using Base::capacity;

        pair<iterator, bool> insert(const value_type& val)
        {
            assert(invariant());
            bool found(true);
            iterator it = lower_bound(val.first);
            assert(it == end() || !m_compare(*it, val));
            if (it == end() || m_compare(*it, val))
            {
                it = Base::insert(it, val);
                found = false;
            }
            assert(invariant());
            return pair<iterator, bool>(it, !found);
        }
        inline  pair<iterator, bool> insert(const key_type& k, const mapped_type& v)
        {
         	return insert(value_type(k, v));
        }

        iterator find(const key_type& k)
		{
			assert(invariant());
		  	iterator i(lower_bound(k));
			if (i != end() && m_compare(k, *i))
			{
		     	i = end();
		   	}
			return i;
		}
    	const_iterator find(const key_type& k) const
    	{       
       		assert(invariant());
        	const_iterator i(lower_bound(k));
        	if (i != end() && m_compare(k, *i))
        	{
              	i = end();
          	}
        	return i;
        }

        inline iterator erase(iterator it)
        {
         	assert(invariant());
         	return Base::erase(it);
        }
        size_type erase(const key_type& k)
    	{
          	iterator i(find(k));
        	if (i == end()) 
               	return 0;
        	erase(i);
          	assert(invariant());
        	return 1;
        }

        using Base::clear;
        using Base::get_allocator;
        using Base::set_allocator;

        iterator lower_bound(const key_type& k)
        {
         	return std::lower_bound(begin(), end(), k, m_compare);
        }
        const_iterator lower_bound(const key_type& k) const
        {
          	return std::lower_bound(begin(), end(), k, m_compare);
        }
        iterator upper_bound(const key_type& k)
        {
          	return std::upper_bound(begin(), end(), k, m_compare);
        }
        const_iterator upper_bound(const key_type& k) const
        {
          	return std::upper_bound(begin(), end(), k, m_compare);
        }
	private:
        sorted_vector(const sorted_vector&);
        sorted_vector& operator=(const sorted_vector&);

        bool invariant() const
        {
            const_iterator first = begin();
            const_iterator last = end();
            assert(last >= first);
            if (first != last)
            {
                    const_iterator next = first;
                    if (++next != last)
                    {
                            assert(m_compare(*first, *next));
                            first = next;
                    }
            }
            return true;
        }
		internal::compare_func<value_type, TCompare>    m_compare;
	};
}
#endif
