#include <iob.h>


unsigned char enabled;


void outb( unsigned short port, unsigned char data )
	{
	    __asm__ __volatile__(
        "outb %1, %0\n"
        :
        : "dN" ( port ), "a" ( data )
    );
	}
DWORD farpeekl( WORD sel, void * off )
	{
	    DWORD ret;
	    asm( "push %%fs\n\t"
		 "mov  %1, %%fs\n\t"
		 "mov  %%fs:(%2), %0\n\t"
		 "pop  %%fs"
		 : "=r"(ret) : "g"(sel), "r"(off) );
	    return ret;
	}
void farpokeb( WORD sel, void *off, BYTE v )
	{
	    asm( "push %%fs\n\t"
		 "mov  %0, %%fs\n\t"
		 "movb %2, %%fs:(%1)\n\t"
		 "pop %%fs"
		 : : "g"(sel), "r"(off), "r"(v) );
	}
unsigned char inb( unsigned short port )
	{
	     register uint8_t value;
 
		__asm__ __volatile__(
		"inb %1, %0\n"
		: "=a" ( value )
		: "dN" ( port )
		);

		return value;
	}
void io_wait( void )
	{
	    // port 0x80 is used for 'checkpoints' during POST.
	    asm volatile( "outb %%al, $0x80"
		          : : "a"(0) );
	}
int irqEnabled()
	{
		int f;
		asm volatile ( "pushf\n\t"
		   "popl %0"
		   : "=g"(f) );
		return f & ( 1 << 9 );
	}
void lidt( void * base, unsigned short size )
	{
	    struct
	    {
		unsigned short length;
		unsigned long base;
	    } __attribute__((__packed__)) IDTR;
	 
	    IDTR.length = size;
	    IDTR.base = (unsigned long)base;
	    asm( "lidt (%0)"
		 : : "p"(&IDTR) );
	}
	//Read the value in a control register. 
unsigned read_cr0( void )
	{
	    unsigned val;
	    asm volatile( "mov %%cr0, %0"
		          : "=r"(val) );
	    return val;
	}
void rdtsc( DWORD * upper, DWORD * lower )
	{
	    asm volatile( "rdtsc\n"
		          : "=a"(*lower), "=d"(*upper) );
	}
void enable()
	{
		if(!enabled)
		{
			__asm__ __volatile__ ("sti": : );
			enabled=1;
		}
	}

void disable() 
	{
		if(enabled)
		{
			__asm__ __volatile__ ("cli" : :	);
			enabled=0;
		}
	}

void halt()
	{
		__asm__ __volatile__ ("hlt" );
	}
unsigned short inw(unsigned short port)
	{
		unsigned short rv;
		__asm__ __volatile__ ("inw %1, %0" : "=a" (rv) : "dN" (port));
		return rv;
	}
void outw(unsigned short port, unsigned short data)
	{
		__asm__ __volatile__ ("outw %1, %0" : : "dN" (port), "a" (data));
	}
unsigned int inl(unsigned short port)
	{
		register unsigned int val;
		__asm__ __volatile__ ("inl %%dx, %%eax" : "=a" (val) : "d" (port));
		return( val );
	}
void outl(unsigned short port, unsigned int data)
	{
		__asm__ __volatile__ ("outl %%eax, %%dx" : : "d" (port), "a" (data));
	}
void insb(unsigned short port, unsigned char *data, unsigned int count)
	{
		for(;count !=0;count--)
		{
			*data = inb(port);
			data++;
		}
	}
void insw(short port, unsigned short *data, unsigned count)
	{
		for(; count != 0; count--)
		{
			*data = inw(port);
			data++;
		}
	}
void insdw(unsigned short port, unsigned int *data, unsigned int count)
	{
		for(; count != 0; count--)
		{
			*data = inl(port);
			data++;
		}
	}
void outsb(unsigned short port, unsigned char *data, unsigned int count)
	{
		for(; count != 0; count--)
		{
			outb(port, *data);
			data++;
		}
	}
void outsw(short port, unsigned short *data, unsigned count)
	{
		for(; count != 0; count--)
		{
			outw(port, *data);
			data++;
		}
	}
void outsdw(unsigned short port, unsigned int *data, unsigned int count)
	{
		for(; count != 0; count--)
		{
			outl(port, *data);
			data++;
		}
	}
void iodelay()
	{ 
		outl(0x80,
		inl(0x80));
	}
void 			outd(uint16_t port, uint32_t value)
	{
		asm volatile ("out %1, %0" : : "dN" (port), "a" (value));
	}
uint32_t 		ind(uint16_t port)
	{
		uint32_t ret;
        asm volatile ("in %1, %0" : "=a" (ret) : "dN" (port));

    	return ret; 
	}
	
	
	
	

