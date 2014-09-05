#ifndef __PCI_LIST_HPP__
#define __PCI_LIST_HPP__

#include <types.h>

typedef struct 
{
	uint32_t VendorId ;
	char *	 VenNameShort ;
	char *	 VenNameFull ;
}  pci_vendortable_t;

typedef struct 
{
	uint32_t	VendorId ;
	uint32_t	DeviceId ;
	char *	Chip ;
	char *	ChipDesc ;
}  PCI_DEVVENTABLE;
/* class table def */
typedef struct
{
	uint8_t class_base;		
	uint8_t class_sub;		
	uint8_t prog_if;		
	char *desc_base;		
	char *desc_sub;			
	char *desc_prog;	
	
} pci_classtable_t;

pci_vendortable_t	*getVendorTable();
uint32_t			 getVendorTableLen();


PCI_DEVVENTABLE		*getDevVenTable();
uint32_t			 getDevVenTableLen();

pci_classtable_t	*getClassCodeTable();
uint32_t			getClassCodeTableLen();

#endif