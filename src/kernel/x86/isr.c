#include <kernel/isr.h>
#include <iob.h>

struct isr_handler_struct
{
	isr_t interrupt_handlers;
	void* userdata;
};


//isr_t interrupt_handlers[256];
struct isr_handler_struct  interrupt_handlers[256];

void set_handler(uint8_t n, isr_t handler)
{
    interrupt_handlers[n].interrupt_handlers = handler;
    interrupt_handlers[n].userdata = NULL;
}
void set_handlerex(uint8_t n, isr_t handler, void* userdata)
{
	interrupt_handlers[n].interrupt_handlers = handler;
    interrupt_handlers[n].userdata = userdata;
}
void isr_handler(registers_t regs)
{
    uint8_t int_no = regs.int_no & 0xFF;
    
    if (interrupt_handlers[int_no].interrupt_handlers != 0)
    {
        isr_t handler = interrupt_handlers[int_no].interrupt_handlers;
        handler(&regs, interrupt_handlers[int_no].userdata);
    }
    else
    {
    	//printf("unhandled interrupt: %d\n", int_no);
        for(;;);
    }
}
void irq_handler(registers_t regs)
{
    if (regs.int_no >= 40)
    {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);

    if (interrupt_handlers[regs.int_no].interrupt_handlers  != 0)
    {
        //isr_t handler = interrupt_handlers[regs.int_no];
        //handler(&regs);
        isr_t handler = interrupt_handlers[regs.int_no].interrupt_handlers;
        handler(&regs, interrupt_handlers[regs.int_no].userdata);
    }

}