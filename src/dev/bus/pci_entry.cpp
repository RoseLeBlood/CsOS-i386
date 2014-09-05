#include <dev/bus/pci_entry.hpp>
#include <dev/bus/pci_list.hpp>
#include <cxx/stl.hpp>

using namespace dev;
using namespace dev::bus;


pci_entry::pci_entry(uint32_t venid, uint32_t devid)
	: m_VendorId(venid), m_DeviceId(devid)
{
	uint32_t pciEntryVentaleLen 	= getDevVenTableLen();
	PCI_DEVVENTABLE *PciDevTable 	= getDevVenTable();
	
	for(uint32_t i=0; i < pciEntryVentaleLen; i++)
	{
		if(PciDevTable[i].VendorId == m_VendorId && PciDevTable[i].DeviceId == m_DeviceId)
		{
			strcpy(m_Chip, PciDevTable[i].Chip);
			strcpy(m_ChipDesc, PciDevTable[i].ChipDesc);
			
			uint32_t pciVenTableLen 			= getVendorTableLen();
			pci_vendortable_t *pciVendor_table 	= getVendorTable();
			
			for(uint32_t j = 0; j < pciVenTableLen; j++)
			{
				if(m_VendorId == pciVendor_table[j].VendorId)
				{
					strcpy(m_VenNameShort, pciVendor_table[j].VenNameShort);
					strcpy(m_VenNameFull, pciVendor_table[j].VenNameFull);
					break;
				}
			}
		}
	}
}