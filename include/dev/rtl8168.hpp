#ifndef __DEV_SERIAL_OUT_HPP__
#define __DEV_SERIAL_OUT_HPP__

#include <dev/Driver.hpp>
#include <iob.h>


namespace dev
{
	typedef struct
	{
	    uint32_t command;  // command/status dword
	    uint32_t vlan;     // currently unused
	    uint32_t low_buf;  // low 32-bits of physical buffer address
	    uint32_t high_buf; // high 32-bits of physical buffer address
	} __attribute__((packed)) RTL8168_Desc;

	typedef struct
	{
	    network_adapter_t* device;
	    RTL8168_Desc*      Rx_Descriptors;
	    RTL8168_Desc*      Tx_Descriptors;
	    uint8_t*           RxBuffer;
	    void*              MMIO_base;
	} RTL8168_networkAdapter_t;


	class rtl8186 : public Driver
	{
	public:
		rtl8186() ;
		virtual bool Probe();
		
		
	protected:
		virtual void  driver_callback(registers_t* reg);
		
	private:
		
	};
}
#endif