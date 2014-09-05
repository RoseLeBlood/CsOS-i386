#ifndef _STDC_IOB_H_
#define _STDC_IOB_H_

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif


void 			outb( unsigned short port, unsigned char val );
DWORD 			farpeekl( WORD sel, void * off );
void 			farpokeb( WORD sel, void *off, BYTE v );
unsigned char 	inb( unsigned short port );
void 			io_wait( void );
int 			irqEnabled();
void 			lidt( void * base, unsigned short size ); 
unsigned 		read_cr0( void );
void 			rdtsc( DWORD * upper, DWORD * lower );
void 			enable();
void 			disable() ;
void 			halt();
unsigned short 	inw(unsigned short port);
void 			outw(unsigned short port, unsigned short data);
unsigned int 	inl(unsigned short port);
void 			outl(unsigned short port, unsigned int data);
void 			insb(unsigned short port, unsigned char *data, unsigned int count);
void 			insw(short port, unsigned short *data, unsigned count);
void 			insdw(unsigned short port, unsigned int *data, unsigned int count);
void 			outsb(unsigned short port, unsigned char *data, unsigned int count);
void 			outsw(short port, unsigned short *data, unsigned count);
void 			outsdw(unsigned short port, unsigned int *data, unsigned int count);
void 			iodelay();
	
void 			outd(uint16_t port, uint32_t value);
uint32_t 		ind(uint16_t port);


#ifdef __cplusplus
}
#endif


#endif
