#ifndef __CSOS_HPP_LOCKED__
#define __CSOS_HPP_LOCKED__

#include <kernel/atomic.h>
#define Lock(x) if (std::csos::SectionBlock __csc = (x))

namespace std
{
	namespace csos
	{
		class Section
		{
		public:
			virtual void Enter( void ) = 0;
			virtual bool TryEnter( void ) = 0;
			virtual void Leave( void ) = 0;
			
			virtual bool IsLocked( void ) = 0;
		};
		class SectionBlock
		{
		public:
			SectionBlock(Section* rc) :  m_rc(rc) { m_rc->Enter(); }
			~SectionBlock(void) { m_rc->Leave(); }
			
			operator bool() { return true; }
		private:
			Section*		m_rc;
		};
	
		
	
		class AtomicSection : public Section
		{
		public:
			AtomicSection();
			virtual ~AtomicSection();
			
			virtual void Enter( void );
			virtual bool TryEnter( void );
			virtual void Leave( void );
		
			virtual bool IsLocked( void );
		private:
			lock_t		m_locked;
		};
		
		
		
		
	}
}
#endif