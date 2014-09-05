#ifndef __LOCKABLE_H_
#define __LOCKABLE_H_

#include <types.h>

#ifdef __cplusplus
extern "C" 
{
#endif
typedef unsigned int lock_t;

void atomicCreate(lock_t* lock);
void atomicDestroy(lock_t* lock);

void atomicLock(lock_t* lock);
bool atomicTryLock(lock_t* lock);
bool atomicIsLock(lock_t* lock);
void atomicUnLock(lock_t* lock);



#ifdef __cplusplus
}
#endif

#endif