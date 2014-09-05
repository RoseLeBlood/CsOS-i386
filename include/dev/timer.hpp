#ifndef _DRIVER_INIT_TIMER_H_
#define _DRIVER_INIT_TIMER_H_

#include <dev/Driver.hpp>
#include <time.h>

namespace dev
{
	class StdTimer : public Driver
	{
	public:
		StdTimer();
		~StdTimer();	
		
		void 		Sleep(int ms);
		
		tm 			GetRunnTime();
		uint64_t 	GetTick();
		
		virtual bool Probe();
	protected:
		virtual void callback(registers_t *reg);
	public:
		static uint64_t ticks;
		static tm	m_clock;
	};
};

#endif
