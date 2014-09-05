#include <klibc/atomic.h>

void atomic_add(atomic_t* dest, int value)
{
  __asm__ __volatile__ (
    "xaddl %1, %0"
    : "=m" (*dest)
    : "ir" (value), "m" (*dest));
}

int atomic_increment(atomic_t* dest) 
{
  int tmp;

  __asm__ __volatile__ (
    "xaddl %0, %1"
    : "=r" (tmp), "=m" (*dest)
    : "0" (1), "m" (*dest));

  return tmp + 1;
}

int atomic_decrement(atomic_t* dest)
{
  int tmp;

  __asm__ __volatile__ (
    "xaddl %0, %1"
    : "=r" (tmp), "=m" (*dest)
    : "0" (-1), "m" (*dest));

  return tmp + 1;
}

int atomic_exchange(atomic_t* dest, unsigned int value) 
{
  __asm__ __volatile__ (
    "xchgl %0, %1"
    : "=r" (value)
    : "m" (*dest), "0" (value)
    : "memory");

  return value;
}

int atomic_compare_and_exchange(atomic_t* dest, int exchange, int comperand) 
{
  int old;

  __asm__ __volatile__ (
    "cmpxchgl %2, %0"
    : "=m" (*dest), "=a" (old)
    : "r" (exchange), "m" (*dest), "a" (comperand));    
  
  return old;
}
void atomic_create(atomic_t* lock)
{
	*lock = 0;
}
void atomic_destroy(atomic_t* lock)
{
	if(*lock != 0)
		atomic_unLock(lock);
}
void atomic_lock(atomic_t* lock)
{
	uint32_t newVal = 1;
    while (atomic_exchange(lock, newVal) == 1) { }
}
bool atomic_tryLock(atomic_t* lock)
{
	uint32_t newVal = 1;
    return (atomic_exchange(lock, newVal) == 0);
}
bool atomic_isLock(atomic_t* lock)
{
	return *lock;
}
void atomic_unLock(atomic_t* lock)
{
	*lock = 0;
}