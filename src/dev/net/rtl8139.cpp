#include <dev/net/rtl8139.hpp>
#include <dev/bus/PciBus.hpp>
#include <kernel/kernel.hpp>
#include <kernel/mm.h>
#include <assert.h>
#include <string.h>
#include <sleep.h>

#define RTL8139_RX_BUFFER_SIZE 0x2000 // 8 KiB
#define RTL8139_TX_BUFFER_SIZE 4096

#define PCI_COMMAND 0x04

#define PCI_CMD_IO        1 << 0
#define PCI_CMD_MMIO      1 << 1
#define PCI_CMD_BUSMASTER 1 << 2

namespace dev
{
	//getDevice(int vendor, int device)
	bus::pci_entry Rtl8139Driver::m_pciList[] = 
	{
	          //0x10EC, 0x8139,     /* Realtek RTL8139 */
	         bus::pci_entry( 0x02ac, 0x1012),     /* SpeedStream 1012 PCMCIA 10/100 */
	         bus::pci_entry( 0x1065, 0x8139),     /* Texas Microsystems 8139C Network Card */
	         bus::pci_entry( 0x1113, 0x1211),     /* Accton MPX5030 or SMC1211TX EZCard 10/100 */
	         bus::pci_entry( 0x1186, 0x1300),     /* D-Link DFE530TX+/DFE538TX */
	         bus::pci_entry( 0x1186, 0x1340),     /* D-Link DFE690TXD */
	         bus::pci_entry( 0x11db, 0x1234),     /* Sega Dreamcast HIT-400 */
	         bus::pci_entry( 0x1259, 0xa117),     /* Allied Telesyn 8139 */
	         bus::pci_entry( 0x1259, 0xa11e),     /* Allied Telesyn 8139 */
	         bus::pci_entry( 0x126c, 0x1211),     /* Northern Telecom 10/100BaseTX*/
	         bus::pci_entry( 0x13d1, 0xab06),     /* AboCom FE2000VX */
	         bus::pci_entry( 0x1432, 0x9130),     /* Edimax Computer Co. RTL81xx */
	         bus::pci_entry( 0x14ea, 0xab06),     /* Planex FNW-3603-TX */
	         bus::pci_entry( 0x14ea, 0xab07),     /* Planex FNW-3800-TX */
	         bus::pci_entry( 0x1500, 0x1360),     /* Delta Electronics RealTek Ethernet */
	         bus::pci_entry( 0x1743, 0x8139),     /* Peppercon AG 8139  ROL/F-100 */
	         bus::pci_entry( 0x4033, 0x1360),     /* Addtron Technology 8139 */
	         bus::pci_entry( 0x0000, 0x0000) 
	};

	Rtl8139Driver::Rtl8139Driver() : NetworkDriver("rtl8139 compatible")
	{
	}
	Rtl8139Driver::~Rtl8139Driver()
	{
	}
	bool Rtl8139Driver::CheakForDev()
	{
		dev::bus::pci_bus *bus = ((dev::bus::pci_bus*)(Kernel::Instance().GetDriver("pci0")));
		
		for(int i = 0; i < 18; i ++)
		{
			memcpy(m_device, bus->getDevice(&m_pciList[i]), sizeof(bus::pci_entry) );
			if(! memcmp(m_device , bus->getDevice(&m_pciList[i]), sizeof(bus::pci_entry) ) )
				return true;
		}
		
		
		return false;
	}
	bool Rtl8139Driver::Probe()
	{
		return ( CheakForDev() );
		
	    
    	setHandler(IRQ0 + m_device->m_irq);
		return false;
	}
	uint64_t Rtl8139Driver::Write(uint8_t *data, uint64_t offset, uint64_t size)
	{
	    memcpy(m_TxBuffer, data, size); // tx buffer
	    if (size < 60) // Fill buffer to a minimal length of 60
	    {
	        memset(m_TxBuffer, 0, 60-size);
	        size = 60;
	    }
	    //printf("\n\n>>> Transmission starts <<<\nPhysical Address of Tx Buffer = %Xh\n", rAdapter->TxBufferPhys);


	    // set address and size of the Tx buffer
	    // reset OWN bit in TASD (REG_TRANSMIT_STATUS) starting transmit
	    // set transmit FIFO threshhold to 48*32 = 1536 bytes to avoid tx underrun
	    *((uint32_t*)(m_MMIO_base + RTL8139_TXADDR0   + 4 * m_TxBufferIndex)) = m_TxBufferPhys;
	    *((uint32_t*)(m_MMIO_base + RTL8139_TXSTATUS0 + 4 * m_TxBufferIndex)) = size | (48 << 16);

	    m_TxBufferIndex++;
	    m_TxBufferIndex %= 4;

	    //printf("\n>> Packet sent. <<");

	    return true;
	}
	void Rtl8139Driver::callback(registers_t *reg)
	{
	
	}
}
