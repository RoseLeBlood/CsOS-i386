#ifndef SYS_STAT_H
#define SYS_STAT_H

#ifdef __cplusplus
extern "C"
{
#endif


#include <types.h>
#include <stddef.h>

#define _SC_OPEN_MAX 4

ssize_t read(int , void *, size_t);
ssize_t write(int fildes, const void *buf, size_t nbyte);
int close(int);

#ifdef __cplusplus
}
#endif

#endif
