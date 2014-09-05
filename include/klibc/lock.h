#ifndef _STDC_LOCK_H_
#define _STDC_LOCK_H_

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif


#define LOCK_LOCKED 1
#define LOCK_UNLOCKED 0

typedef volatile uint8_t lock_t;

void lock(lock_t* l);
void unlock(lock_t* l);
bool locked(lock_t* l);
void lock_wait(lock_t* l);

/**
* Eine Variable Inkrementieren, waerend der Bus gesperrt ist.
*
* @param var Pointer auf die zu inkrementierende Variable
*/
/*static inline uint32_t locked_increment(volatile uint32_t* var)
{
	return __sync_fetch_and_add(var, 1);
}*/



#ifdef __cplusplus
}
#endif

#endif
