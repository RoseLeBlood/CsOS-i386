#ifndef _STDC_STDDEF_H_
#define _STDC_STDDEF_H_

#undef NULL
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL (void*)0
#endif

#define NAN (__builtin_nanf(""))

typedef __SIZE_TYPE__		size_t;
typedef __PTRDIFF_TYPE__		ptrdiff_t;

#ifdef __GNUC__
typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __SIZE_TYPE__ size_t;
#ifndef __cplusplus
typedef __WCHAR_TYPE__ wchar_t;
#endif
#else
typedef signed long ptrdiff_t;
typedef unsigned long size_t;
typedef int wchar_t;
#endif

#undef offsetof
#define offsetof(type,member) ((size_t) &((type*)0)->member)


#define BYTE1(a) ( (a)      & 0xFF)
#define BYTE2(a) (((a)>> 8) & 0xFF)
#define BYTE3(a) (((a)>>16) & 0xFF)
#define BYTE4(a) (((a)>>24) & 0xFF)

#define max(a, b) ((a) >= (b) ? (a) : (b))
#define min(a, b) ((a) <= (b) ? (a) : (b))



#define BIT(n) (1<<(n))
#define IS_BIT_SET(value, pos) ((value)&BIT(pos))

#define SAFE_DELETE(c)	if(c != NULL) { delete c; c = NULL; }







#endif
