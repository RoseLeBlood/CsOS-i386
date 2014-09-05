#ifndef _STD_ALLOCATOR_H_
#define _STD_ALLOCATOR_H_

#include <string.h>

namespace std
{
	class allocator
	{
	public:
	        explicit allocator(const char* name = "def"):       m_name(name) {}
	        ~allocator() {}


	        void* allocate(unsigned int bytes, int flags = 0);
	     
	        void* allocate_aligned(unsigned int bytes, unsigned int alignment, int flags = 0);
	        void deallocate(void* ptr, unsigned int bytes);

	        const char* get_name() const { return m_name; }
	private:
	        const char*     m_name;
	};

	inline bool operator==(const allocator& lhs, const allocator& rhs)
	{
	        return !strcmp(lhs.get_name(), rhs.get_name());
	}
	inline bool operator!=(const allocator& lhs, const allocator& rhs)
	{
	        return !(lhs == rhs);
	}

	inline void* allocator::allocate(unsigned int bytes, int)
	{
	        return operator new(bytes);
	}

	inline void allocator::deallocate(void* ptr, unsigned int)
	{
	        operator delete(ptr);
	}
}

#endif
