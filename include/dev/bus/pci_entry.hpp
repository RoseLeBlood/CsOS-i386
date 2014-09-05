#ifndef __PCI_ENTRY_HPP___
#define __PCI_ENTRY_HPP___

#include <types.h>
#include <string.h>

namespace dev
{
	namespace bus
	{
		struct pci_entry
		{
			pci_entry(uint32_t venid, uint32_t devid);
			
			uint32_t	m_VendorId ;
			uint32_t	m_DeviceId ;
			char		m_Chip[128];
			char		m_ChipDesc[128];
			char	 	m_VenNameShort [256];
			char	 	m_VenNameFull [256];
		};
		inline bool operator == (pci_entry s1, pci_entry s2)
		{	
			return (s1.m_VendorId == s2.m_VendorId) && (s2.m_DeviceId == s1.m_DeviceId);
		}
	}
}




#endif