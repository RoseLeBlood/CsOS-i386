#ifndef KLIBC_STDARG_H
#define KLIBC_STDARG_H


#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>

#define va_start(ap, X)         __builtin_va_start(ap, X)
#define va_arg(ap, type)        __builtin_va_arg(ap, type)
#define va_end(ap)              __builtin_va_end(ap) 
#define va_copy(d,s)			__builtin_va_copy(d,s)


typedef __builtin_va_list       va_list;


#ifdef __cplusplus
};
#endif


#endif
