#ifndef __DEVICE_RANDOM_HPP__
#define __DEVICE_RANDOM_HPP__

#include <dev/Driver.hpp>

namespace dev
{
	class std_random : public Driver
	{
	public:
		std_random();
		std_random(char* name, char* devname) : Driver(name, devname, true, false) { }
		
		// offset = max, size = anzahl, return größte
		virtual uint64_t Read(uint8_t *data, uint64_t offset, uint64_t size);
		virtual uint64_t Write(uint8_t *data, uint64_t offset, uint64_t size) { return 0; }

		virtual bool Probe() { return true; }
		
		uint32_t rand();
		void srand( uint32_t seed );
		uint32_t rand(int min, int max);	
		
		virtual char ReadChar() { return (char)rand(0, 0xff); }	
	};
};



#endif