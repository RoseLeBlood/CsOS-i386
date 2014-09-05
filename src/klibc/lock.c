#include <klibc/lock.h>

void lock(lock_t* l)
{
	asm("movb $1, %%cl;"
           "lock_loop: xorb %%al, %%al;"
           "lock cmpxchgb %%cl, (%0);"
           "jnz lock_loop;" : : "D" (l) : "eax", "ecx");
}
void unlock(lock_t* l)
{
	*l = 0;
}
bool locked(lock_t* l)
{
	return *l;
}
void lock_wait(lock_t* l)
{
	 while (locked(l)) asm("nop");
}
