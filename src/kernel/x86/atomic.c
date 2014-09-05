#include <kernel/atomic.h>


extern int atomicExchange(void* lock, unsigned int value);

void atomicCreate(lock_t* lock)
{
	*lock = 0;
}
void atomicDestroy(lock_t* lock)
{
	if(*lock != 0)
		atomicUnLock(lock);
}

void atomicLock(lock_t *lock)
{
    uint32_t newVal = 1;
    while (atomicExchange(lock, newVal) == 1) { }
}
bool atomicTryLock(lock_t *lock)
{
	// Spin once.
    uint32_t newVal = 1;
    return (atomicExchange(lock, newVal) == 0);
}
bool atomicIsLock(lock_t *lock)
{
	return *lock;
}
void atomicUnLock(lock_t *lock)
{
	*lock = 0;
}