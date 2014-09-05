#include <dev/dma.hpp>
#include <iob.h>

namespace dev
{
	void drvDma::dmaDo(dma_packed_t* data, int mode)
	{
		data->dmaLength--; // ISA DMA counts from 0

	    outb(0x0A,                 			(1 << 2) | data->dmaChannel.portNum); // Mask channel
	    outb(data->dmaChannel.pagePort,    (uintptr_t)data->dmaData >> 16);  	 // Address: Bits 16-23 (External page register. Allows us to address up to 16 MiB)
	    outb(0x0C,                 			0x00);                      		 // Reset flip-flop
	    outb(data->dmaChannel.addressPort, (uintptr_t)data->dmaData);        	 // Address: Bits 0-7
	    outb(data->dmaChannel.addressPort, (uintptr_t)data->dmaData >> 8);   	 // Address: Bits 8-15
	    outb(0x0C,                 			0x00);                      		 // Reset flip-flop
	    outb(data->dmaChannel.counterPort, data->dmaLength);                    // Length: Lower byte
	    outb(data->dmaChannel.counterPort, data->dmaLength >> 8);               // Length: Higher byte
	    outb(0x0B,                 			mode | data->dmaChannel.portNum);   // Mode
	    outb(0x0A,                 			data->dmaChannel.portNum);          // Unmask channel
	}
	uint64_t drvDma::Read(uint8_t *packed, uint64_t offset, uint64_t size) 
	{ 
		uint64_t k = 0;
		dma_packed_t *data = (dma_packed_t*)packed;
		
		while(data != NULL)
		{
			k++;
			dmaDo(data, data->dmaMode | DmaTransferMode::Read);
			data = data->dmaNext;
		}
		return k * sizeof(dma_packed_t); 
	}
	uint64_t drvDma::Write(uint8_t *packed, uint64_t offset, uint64_t size) 
	{ 
		uint64_t k = 0;
		dma_packed_t *data = (dma_packed_t*)packed;
		
		while(data != NULL)
		{
			k++;
			dmaDo(data, data->dmaMode | DmaTransferMode::Write);
			data = data->dmaNext;
		}
		return k * sizeof(dma_packed_t); 
	}
}