#include <dev/bus/PciBus.hpp>
#include <iob.h>
#include <string.h>
#include <malloc.h>
#include <dev/bus/pci_list.hpp>
#include <cxx/stl.hpp>
#include <string.h>

using namespace dev;
using namespace dev::bus;

#define PCI_CONFIGURATION_ADDRESS 0x0CF8
#define PCI_CONFIGURATION_DATA    0x0CFC

pci_bus::pci_bus() : dev::Driver("Peripheral Component Interconnect driver ö", "pci")
{
	
}
pci_bus::~pci_bus()
{
	delete m_devices;
}
void pci_bus::Write(uint8_t bus, uint8_t device, uint8_t func, uint8_t reg, uint8_t val)
{
    outl(PCI_CONFIGURATION_ADDRESS,
        0x80000000
        | (bus     << 16)
        | (device  << 11)
        | (func    <<  8)
        | (reg & 0xFC));

    outb(PCI_CONFIGURATION_DATA + (reg & 0x03), val);
} 

void pci_bus::Write(uint8_t bus, uint8_t device, uint8_t func, uint8_t reg, uint16_t val)
{
    outl(PCI_CONFIGURATION_ADDRESS,
        0x80000000
        | (bus     << 16)
        | (device  << 11)
        | (func    <<  8)
        | (reg & 0xFC));

    outw(PCI_CONFIGURATION_DATA, val);
}

void pci_bus::Write(uint8_t bus, uint8_t device, uint8_t func, uint8_t reg, uint32_t val)
{
    outl(PCI_CONFIGURATION_ADDRESS,
        0x80000000
        | (bus     << 16)
        | (device  << 11)
        | (func    <<  8)
        | (reg & 0xFC));

    outl(PCI_CONFIGURATION_DATA, val);
}

uint32_t                pci_bus::Read(uint32_t bus, uint32_t device, uint32_t function, uint32_t offset, uint8_t size)
{
	uint32_t value;
    outd(0xCF8,  0x80000000 | (bus << 16) | (device << 11) | (function << 8) | (offset & ~3));

    switch (size)
    {
    case 1: 
        value = inb(0xCFC + (offset & 3)); 
        break;

    case 2: 
        value = inw(0xCFC + (offset & 2)); 
        break;

    case 4: 
        value = ind(0xCFC); 
        break;

    default:
   		return 0xFF;
    }
    return value;
}
pci_dev *pci_bus::getBusDevice(uint32_t bus, uint32_t device, uint32_t func)
{
	unsigned i;
	
    uint32_t tmp = Read(bus, device, func, VENDOR_ID, 2);
    if ((tmp == 0xFFFF) || (tmp == 0x0000)) 
            return NULL;

    pci_dev *pci_dev = new dev::bus::pci_dev();

    pci_dev->m_Bus = bus;
    pci_dev->m_Device = device;
    pci_dev->m_Function = func;

	pci_dev->m_entry = new pci_entry(Read(bus, device, func, VENDOR_ID, 2),
							   Read(bus, device, func, DEVICE_ID, 2));
							   
    pci_dev->m_Command = Read(bus, device, func, COMMAND, 2);
    pci_dev->m_Status = Read(bus, device, func, STATUS, 2);

    pci_dev->m_ClassId = Read(bus, device, func, CLASS_BASE, 1);
    pci_dev->m_SubclassId = Read(bus, device, func, CLASS_SUB, 1);

	uint8_t headerType = Read(bus, device, 0, HEADER_TYPE, 1);
	
    for(i = 0; i < 6; i++)
    {
    	pci_dev->m_bar[i].baseAddress = Read(bus, device, func, BASE_REGISTERS + (i * 4), 4);
    	
    	if (i < 2 || !(headerType & 0x01)) // Devices with header type 0x00 have 6 bars
        {
	        if (pci_dev->m_bar[i].baseAddress) // Valid bar
	        {
	            // Check memory type
	            pci_dev->m_bar[i].memoryType = (pci_mem::pci_mem_t)(pci_dev->m_bar[i].baseAddress & 0x01);
	            if (pci_dev->m_bar[i].memoryType == 0) // MMIO bar
	                pci_dev->m_bar[i].baseAddress &= 0xFFFFFFF0;
	            else                               // IO bar
	                pci_dev->m_bar[i].baseAddress &= 0xFFFC;

	            // Check Memory Size
	            
	            asm("cli");
	            Write(bus, device, func, BASE_REGISTERS + (i * 4), 0xFFFFFFFF);
	            pci_dev->m_bar[i].memorySize = (~(Read(bus, device, func, BASE_REGISTERS + (i * 4), 4)) | 0x0F) + 1;
	            Write(bus, device, func, BASE_REGISTERS + (i * 4), pci_dev->m_bar[i].baseAddress);
	            asm("sti");
	        }
	        else
	       		pci_dev->m_bar[i].memoryType = pci_mem::INVA;
	    }
		else
	    	pci_dev->m_bar[i].memoryType = pci_mem::INVA;
	}
    pci_dev->m_IntLine = Read(bus, device, func, INTERRUPT_LINE, 1);
    pci_dev->m_IntPin = Read(bus, device, func, INTERRUPT_PIN, 1);
    
    uint32_t pciClassCodeLen = getClassCodeTableLen();
    pci_classtable_t *pci_class_code_table = getClassCodeTable();
    
    for(i = 0; i < pciClassCodeLen; i++)
    if(     (pci_class_code_table[i].class_base == pci_dev->m_ClassId) &&
            (pci_class_code_table[i].class_sub == pci_dev->m_SubclassId))
    {
            strcpy(pci_dev->m_Class, pci_class_code_table[i].desc_base);
            strcpy(pci_dev->m_ClassDesc, pci_class_code_table[i].desc_sub);
            
            break;
    }

    return pci_dev;
}
uint32_t                pci_bus::Update()
{
	unsigned n = 0;
    unsigned int bus, device, func;
    
    m_devices->clear();

    for(bus = 0; bus < 16; bus++)
    	for(device = 0; device < 12; device++)
            for(func = 0; func < 12; func++)
            {
	            pci_dev *newdev = getBusDevice(bus, device, func);
	            if(newdev != NULL)
	            {
            		m_devices->push_back(newdev);
                    n++;
	            }
            }
    return n;

}

pci_dev *				pci_bus::getDevice(pci_entry* m)
{
	for(std::list<pci_dev*>::iterator i = m_devices->begin() ; i != m_devices->end(); i++)
	{
		if((*i)->m_entry == m)
			return (*i);
	}
	return NULL;
}
std::list<pci_dev*>*  	pci_bus::getDeviceList()
{
	return m_devices;
}
bool pci_bus::Probe()
{
	m_devices = new std::list<pci_dev*>();
	Update();
	return true;
}
void pci_bus::Dump()
{
	std::list<dev::bus::pci_dev*> *list = getDeviceList();
	
	for(std::list<dev::bus::pci_dev*>::iterator i = list->begin() ; i != list->end(); i++)
	{
		std::cout << std::flags::hex << (*i)->m_Bus << ":" << (*i)->m_Function << "." << (*i)->m_Device << " " <<
					 (*i)->m_Class << ": " << (*i)->m_entry->m_VenNameShort << " " << (*i)->m_entry->m_ChipDesc 
				  << std::flags::dec << "( " << (*i)->m_irq << " )"<< std::endl;
	}
}





