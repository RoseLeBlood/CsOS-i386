#include <dev/timer.hpp>
#include <cxx/iostream.hpp>

#include <time.h>
#include <iob.h>

#include <string.h>

//struct tm *localtime
extern void* kernel_instance;

extern "C" void sthreadRun();
extern "C" void sthreadSwitch();

namespace dev
{
	uint64_t StdTimer::ticks = 0;
	tm	StdTimer::m_clock;
	
	StdTimer::StdTimer() : Driver("Timer", "tm", false, false)
	{
	
	}
	StdTimer::~StdTimer()
	{
	
	}		
	void StdTimer::callback(registers_t *reg)
	{
		ticks++;
		sthreadRun();
		
		
		if(ticks%2 == 0)
		{
			sthreadSwitch();
		}
		else if(ticks%100 == 0)
        {
                m_clock.tm_sec++;
                if(m_clock.tm_sec >= 60)
                {
                        m_clock.tm_sec = 0;
                        m_clock.tm_min++;
                }
                if(m_clock.tm_min >= 60)
                {
                        m_clock.tm_min = 0;
                        m_clock.tm_hour++;
                }
                if(m_clock.tm_hour >= 23)
                {
                        m_clock.tm_hour = 0;
                        m_clock.tm_mday++;
                }
                if(m_clock.tm_mday >= 30)
                {
                        m_clock.tm_mday = 0;
                        m_clock.tm_mon++;
                }
                if(m_clock.tm_mon >= 12)
                {
                        m_clock.tm_mon = 0;
                        m_clock.tm_year++;
                }
        }
	}
	uint64_t StdTimer::GetTick()
	{
		return ticks;
	}
	tm StdTimer::GetRunnTime()
	{
		return m_clock;
	}
	bool StdTimer::Probe()
	{
		ticks = 0;

		setHandler(IRQ0);
		
        uint32_t divisor = 1193180 / 50;

	    // Send the command byte.
	    outb(0x43, 0x36);

	    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
	    uint8_t l = (uint8_t)(divisor & 0xFF);
	    uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );

	    // Send the frequency divisor.
	    outb(0x40, l);
	    outb(0x40, h);
	    
	    return true;
	}
	void StdTimer::Sleep(int ms)
	{
		uint64_t cur;
		cur=GetTick();
		
		while(cur+ms != GetTick());
	}
}