#ifndef _STD_ITERATOR_H_
#define _STD_ITERATOR_H_

#include "common.hpp"

namespace std
{

	//-----------------------------------------------------------------------------
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	//-----------------------------------------------------------------------------
	template<typename IterT>
	struct iterator_traits 
	{
	   typedef typename IterT::iterator_category iterator_category;
	};

	template<typename T>          
	struct iterator_traits<T*> 
	{
	   typedef random_access_iterator_tag iterator_category;
	};

	//-----------------------------------------------------------------------------
	namespace internal
	{
	        template<typename TIter, typename TDist> inline
	        void distance(TIter first, TIter last, TDist& dist, std::random_access_iterator_tag)
	        {
	                dist = TDist(last - first);
	        }
	        template<typename TIter, typename TDist> inline
	        void distance(TIter first, TIter last, TDist& dist, std::input_iterator_tag)
	        {
	                dist = 0;
	                while (first != last)
	                {
	                        ++dist;
	                        ++first;
	                }
	        }

	        template<typename TIter, typename TDist> inline
	        void advance(TIter& iter, TDist d, std::random_access_iterator_tag)
	        {
	                iter += d;
	        }
	        template<typename TIter, typename TDist> inline
	        void advance(TIter& iter, TDist d, std::bidirectional_iterator_tag)
	        {
	                if (d >= 0)
	                {
	                        while (d--)
	                                ++iter;
	                }
	                else
	                {
	                        while (d++)
	                                --iter;
	                }
	        }
	        template<typename TIter, typename TDist> inline
	        void advance(TIter& iter, TDist d, std::input_iterator_tag)
	        {
	                assert(d >= 0);
	                while (d--)
	                        ++iter;
	        }
	} 
}
#endif