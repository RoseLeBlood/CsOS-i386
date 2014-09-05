#ifndef __PCI_DEVICE_HPP___
#define __PCI_DEVICE_HPP___

#include <types.h>
#include <string.h>
#include <dev/bus/pci_entry.hpp>
#include <cxx/stl.hpp>

namespace dev
{
	namespace bus
	{
		namespace pci_mem
		{
			enum pci_mem_t
			{
				MMIO, IO, INVA
			};
		}
	
		struct pci_bar
		{
			uint32_t 			baseAddress;
			uint32_t			memorySize;
			pci_mem::pci_mem_t 	memoryType;
		};
		
		
		struct pci_dev
		{
			uint32_t m_Bus;                                  
            uint32_t m_Function;
            uint32_t m_Device;
            uint32_t m_Command;
            uint32_t m_Status;
			uint32_t m_ClassId;                              
            uint32_t m_SubclassId;
            
            union
            {  
            	uint32_t m_IntLine;
            	uint32_t m_irq;
            };
            
            uint32_t m_IntPin;
         
            pci_bar  m_bar[6];

            char m_Class[128];
            char m_ClassDesc[128];
			char m_Vendor[128];
			            
			pci_entry *m_entry;
		};
	}
	
}
#endif