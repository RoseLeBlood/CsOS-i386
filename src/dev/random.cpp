#include <dev/Random.hpp>
#include <kernel/kernel.hpp>
#include <stdlib.h>
#include <time.h>

#define BCD2BIN(bcd) ((((bcd)&15) + ((bcd)>>4)*10))


namespace dev
{
	std_random::std_random() : Driver("Random", "rand", true, false) 
	{
	
	}
	uint32_t std_random::rand()
	{	
		return rand();
	}
	void std_random::srand( uint32_t seed )
	{
		srand(seed);
	}
	uint32_t std_random::rand(int min, int max)
	{
		 //srand(time(NULL));
   		return rand() % (max - min + 1) + min;
	}
	uint64_t std_random::Read(uint8_t *data, uint64_t offset, uint64_t size)
	{
		uint64_t max = 0;
		
		for(uint64_t i = 0; i < size; i++)
		{
			srand(max * rand() & i);
			
			data[i] = rand(0, offset);
			
			if(data[i] > max)
				max = data[i];
		
		}
		return max;
	}
}