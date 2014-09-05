#include <types.h>
#include <atomic.h>
#include <cxx/lock.hpp>

namespace std
{
	namespace csos
	{
		AtomicSection::AtomicSection()
		{
			atomic_create(&m_locked);
		}
		AtomicSection::~AtomicSection()
		{
			atomic_destroy(&m_locked);
		}
		void AtomicSection::Enter( void )
		{
			atomic_lock(&m_locked);
		}
		bool AtomicSection::TryEnter( void )
		{
			return atomic_tryLock(&m_locked);
		}
		void AtomicSection::Leave( void )
		{
			atomic_unLock(&m_locked);
		}
		
		bool AtomicSection::IsLocked( void )
		{
			return atomic_isLock(&m_locked);
		}
	}
}
