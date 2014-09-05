
#include <assert.h>
#include <types.h>
#include <stdio.h>
#include <iob.h>

void __assert(const char *ext, const char *file, int line)
{
	asm volatile("cli");
	printf("assertion failed in file %s, line %d:\n", file, line);
	printf("%s\n", ext);
	
	disable();
	halt();
	for(;;) asm("nop");
}
void __panic(const char *message, const char *file, int line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.

	printf("panic: %s at %s : %d\n", message, file, line);

	disable();
	halt();
    for(;;) asm("nop");
}