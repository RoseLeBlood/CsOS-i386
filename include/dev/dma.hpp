#ifndef __DEV_DMA_HPP__
#define __DEV_DMA_HPP__

#include <dev/Driver.hpp>
#include <cxx/stl.hpp>

namespace dev
{
	namespace DmaTransferMode
	{
		enum DmaTransferMode_t
		{
			Write	= (1 << 2),
			Read 	= (1 << 3),
			AutoInit = (1 << 4),
			Increment = 0,
			Decrement = ( 1 << 5),
			Demand = ( 1 << 0),
			Single = ( 1 << 6),
			Block = ( 1 << 7)
		};
	}
	
	typedef struct
	{
		uint8_t  portNum;
		uint16_t pagePort;
		uint16_t addressPort;
		uint16_t counterPort;
	} dma_channel_t;
	/*{{0, 0x87, 0x00, 0x01}, 
	{1, 0x83, 0x02, 0x03}, 
	{2, 0x81, 0x04, 0x05}, 
	{3, 0x82, 0x06, 0x07}};*/
	
				
	typedef struct dmapacked
	{
		dma_channel_t 					   dmaChannel;
		DmaTransferMode::DmaTransferMode_t dmaMode;
		void*	  					   	   dmaData;
		uint64_t	  					   dmaLength;
		
		dmapacked*					   	   dmaNext; /* NYI */
	}dma_packed_t;
	
	
	
	class drvDma : public Driver
	{
	public:
		drvDma() : Driver("Direct Memory Access driver", "dma", true, true) 
		{
		}
		virtual uint64_t Read(uint8_t *packed, uint64_t offset, uint64_t size);
		virtual uint64_t Write(uint8_t *packed, uint64_t offset, uint64_t size);
	private:
		void dmaDo(dma_packed_t* data, int mode);
	};
}	
#endif