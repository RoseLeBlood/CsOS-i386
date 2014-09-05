#ifndef __DEVICE_BUS_PCI_HPP__
#define __DEVICE_BUS_PCI_HPP__

#include <types.h>
#include <dev/Driver.hpp>
#include <cxx/stl.hpp>
#include <dev/bus/pci_entry.hpp>
#include <dev/bus/pci_dev.hpp>



namespace dev
{
	namespace bus
	{
		class pci_bus : public dev::Driver
		{
		public:
			static const unsigned VENDOR_ID      = 0x00; /* (2 byte) vendor id */
            static const unsigned DEVICE_ID      = 0x02; /* (2 byte) device id */
            static const unsigned COMMAND        = 0x04; /* (2 byte) command */
            static const unsigned STATUS         = 0x06; /* (2 byte) status */
            static const unsigned REVISION_ID    = 0x08; /* (1 byte) revision id */
            static const unsigned CLASS_API      = 0x09; /* (1 byte) specific register interface type */
            static const unsigned CLASS_SUB      = 0x0A; /* (1 byte) specific device function */
            static const unsigned CLASS_BASE     = 0x0B; /* (1 byte) device type (display vs network, etc) */
            static const unsigned LINE_SIZE      = 0x0C; /* (1 byte) cache line size in 32 bit words */
            static const unsigned LATENCY        = 0x0D; /* (1 byte) latency timer */
            static const unsigned HEADER_TYPE    = 0x0E; /* (1 byte) header type */
            static const unsigned BIST           = 0x0F; /* (1 byte) built-in self-test */
            static const unsigned BASE_REGISTERS = 0x10; /* base registers (size varies) */
            static const unsigned SUBSYS_VEND_ID = 0x2C; /* (2 byte) subsystem vendor id */
            static const unsigned SUBSYS_DEV_ID  = 0x2E; /* (2 byte) subsystem id */
            static const unsigned INTERRUPT_LINE = 0x3C; /* (1 byte) interrupt line */
            static const unsigned INTERRUPT_PIN  = 0x3D;
            
		public:
			pci_bus();
			~pci_bus();
		
			virtual bool Probe();
		
			uint32_t                Read(uint32_t bus, uint32_t device, uint32_t function, uint32_t offset, uint8_t size);
            
            void 					Write(uint8_t bus, uint8_t device, uint8_t func, uint8_t reg, uint8_t val);
			void 				    Write(uint8_t bus, uint8_t device, uint8_t func, uint8_t reg, uint16_t val);
			void 					Write(uint8_t bus, uint8_t device, uint8_t func, uint8_t reg, uint32_t val);
            
            pci_dev *               getBusDevice(uint32_t bus, uint32_t device, uint32_t func);
            uint32_t                Update();
            
            pci_dev *				getDevice(pci_entry* m);
            pci_dev *				getDevice(int vendor, int device);
            
			std::list<pci_dev*>*  	getDeviceList();
		
			void					Dump();					
		private:
			std::list<pci_dev*>			*m_devices;
		};
	}
};
#endif