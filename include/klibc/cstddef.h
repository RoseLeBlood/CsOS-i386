#ifndef __KLIBC_CSTDDEF_H__
#define __KLIBC_CSTDDEF_H__

#include <stddef.h>

#if defined(__WINT_TYPE__)
typedef __WINT_TYPE__ wint_t;
#else
typedef unsigned int wint_t;
#endif

#endif

