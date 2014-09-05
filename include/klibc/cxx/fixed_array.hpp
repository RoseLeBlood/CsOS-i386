#ifndef RDESTL_FIXED_ARRAY_H
#define RDESTL_FIXED_ARRAY_H

#include "algorithm.h"

namespace std
{
	template<typename T, size_t N> class fixed_array
	{
	        typedef char ERR_N_MustBeBiggerThanZero[N > 0 ? 1 : -1];
	public:
	        typedef T                       value_type;
	        typedef T*                      iterator;
	        typedef const T*        		const_iterator;
	        typedef size_t          		size_type;

	        fixed_array() 
	        {
	        	/**/
	        }
	        fixed_array(const T array[N])
	        {
	                std::copy_n(&array[0], N, m_data);
	        }


	        iterator begin()                               
	        { 
	        	return &m_data[0]; 
	        }
	        const_iterator begin() const    
	        { 
	        	return &m_data[0]; 
	        }
	        iterator end()                                  
	        { 
	        	return begin() + N; 
	        }
	        const_iterator end() const              
	        { 
	        	return begin() + N; 
	        }
	        size_type size() const  
	        { 
	        	return N; 
	        }
	        T* data()                               
	        { 
	        	return &m_data[0]; 
	        }
	        const T* data() const  
	        { 
	        	return &m_data[0]; 
	        }

	        const T& front() const  
	        { 
	        	return *begin(); 
	        }
	        T& front()                              
	        { 
	        	return *begin(); 
	        }
	        const T& back() const   
	        { 
	        	return *(end() - 1); 
	        }
	        T& back()                               
	        { 
	        	return *(end() - 1); 
	        }

	        inline T& operator[](size_type i)
	        {
	                assert(i < size());
	                return m_data[i];
	        }
	        inline const T& operator[](size_type i) const
	        {
	                assert(i < size());
	                return m_data[i];
	        }

	private:
	        T       m_data[N];
	};

} 
#endif 

