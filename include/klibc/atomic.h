#ifndef STDC_ATOMIC_H
#define STDC_ATOMIC_H

#include <types.h>

#ifdef  __cplusplus
extern "C" {
#endif

typedef unsigned int atomic_t;

void atomic_add(atomic_t* dest, int value);
int  atomic_increment(atomic_t* dest);
int  atomic_decrement(atomic_t* dest);
int  atomic_exchange(atomic_t* dest, unsigned int value);
int  atomic_compare_and_exchange(atomic_t* dest, int exchange, int comperand);

void atomic_create(atomic_t* lock);
void atomic_destroy(atomic_t* lock);
void atomic_lock(atomic_t* lock);
bool atomic_tryLock(atomic_t* lock);
bool atomic_isLock(atomic_t* lock);
void atomic_unLock(atomic_t* lock);

#ifdef  __cplusplus
}
#endif

#endif

