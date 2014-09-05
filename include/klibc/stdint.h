#ifndef _STDC_STDINT_H_
#define _STDC_STDINT_H_

#include <klibc/_sizes.h>

#if	__CHAR_BIT__ == 8
typedef char					int8_t;
typedef unsigned char			uint8_t;
#endif

#if	__CHAR_BIT__ >= 8
typedef char					int_least8_t;
typedef unsigned char			uint_least8_t;
#else
#error Could not determine int_least8_t and uint_least8_t
#endif


#if	__CHAR_BIT__ == 16
typedef char					int16_t;
typedef unsigned char			uint16_t;
typedef int16_t					int_least16_t;
typedef uint16_t					uint_least16_t;
#elif	__CHAR_BIT__ * __SIZEOF_SHORT__ == 16
typedef short					int16_t;
typedef unsigned short			uint16_t;
typedef int16_t					int_least16_t;
typedef uint16_t					uint_least16_t;
#elif	__CHAR_BIT__ * __SIZEOF_INT__ == 16
typedef int					int16_t;
typedef unsigned int				uint16_t;
typedef int16_t					int_least16_t;
typedef uint16_t					uint_least16_t;
#elif	__CHAR_BIT__ * __SIZEOF_LONG__ == 16
typedef long					int16_t;
typedef unsigned long			uint16_t;
typedef int16_t					int_least16_t;
typedef uint16_t					uint_least16_t;
#elif	__CHAR_BIT__ * __SIZEOF_LONG_LONG__ == 16
typedef long long				int16_t;
typedef unsigned long long		uint16_t;
typedef int16_t					int_least16_t;
typedef uint16_t					uint_least16_t;
#elif	__CHAR_BIT__ * __SIZEOF_LONG_LONG__ >= 16
typedef long long				int_least16_t;
typedef unsigned long long		uint_least16_t;
#else
#error Could not determine int_least16_t and uint_least16_t
#endif


#if	__CHAR_BIT__ == 32
typedef char					int32_t;
typedef unsigned char			uint32_t;
typedef int32_t					int_least32_t;
typedef uint32_t					uint_least32_t;
#elif	__CHAR_BIT__ * __SIZEOF_SHORT__ == 32
typedef short					int32_t;
typedef unsigned short			uint32_t;
typedef int32_t					int_least32_t;
typedef uint32_t					uint_least32_t;
#elif	__CHAR_BIT__ * __SIZEOF_INT__ == 32
typedef int					int32_t;
typedef unsigned int				uint32_t;
typedef int32_t					int_least32_t;
typedef uint32_t					uint_least32_t;
#elif	__CHAR_BIT__ * __SIZEOF_LONG__ == 32
typedef long					int32_t;
typedef unsigned long			uint32_t;
typedef int32_t					int_least32_t;
typedef uint32_t					uint_least32_t;
#elif	__CHAR_BIT__ * __SIZEOF_LONG_LONG__ == 32
typedef long long				int32_t;
typedef unsigned long long		uint32_t;
typedef int32_t					int_least32_t;
typedef uint32_t					uint_least32_t;
#elif	__CHAR_BIT__ * __SIZEOF_LONG_LONG__ >= 32
typedef long long				int_least32_t;
typedef unsigned long long		uint_least32_t;
#else
#error Could not determine int_least32_t and uint_least32_t
#endif


#if	__CHAR_BIT__ == 64
typedef char					int64_t;
typedef unsigned char			uint64_t;
typedef int64_t					int_least64_t;
typedef uint64_t					uint_least64_t;
#elif	__CHAR_BIT__ * __SIZEOF_SHORT__ == 64
typedef short					int64_t;
typedef unsigned short			uint64_t;
typedef int64_t					int_least64_t;
typedef uint64_t					uint_least64_t;
#elif	__CHAR_BIT__ * __SIZEOF_INT__ == 64
typedef int					int64_t;
typedef unsigned int				uint64_t;
typedef int64_t					int_least64_t;
typedef uint64_t					uint_least64_t;
#elif	__CHAR_BIT__ * __SIZEOF_LONG__ == 64
typedef long					int64_t;
typedef unsigned long			uint64_t;
typedef int64_t					int_least64_t;
typedef uint64_t					uint_least64_t;
#elif	__CHAR_BIT__ * __SIZEOF_LONG_LONG__ == 64
typedef long long				int64_t;
typedef unsigned long long		uint64_t;
typedef int64_t					int_least64_t;
typedef uint64_t					uint_least64_t;
#elif	__CHAR_BIT__ * __SIZEOF_LONG_LONG__ >= 64
typedef long long				int_least64_t;
typedef unsigned long long		uint_least64_t;
#else
#error Could not determine int_least64_t and uint_least64_t
#endif


typedef int_least8_t				int_fast8_t;
typedef uint_least8_t				uint_fast8_t;
typedef int_least16_t				int_fast16_t;
typedef uint_least16_t				uint_fast16_t;
typedef int_least32_t				int_fast32_t;
typedef uint_least32_t				uint_fast32_t;
typedef int_least64_t				int_fast64_t;
typedef uint_least64_t				uint_fast64_t;


#if	__SIZEOF_POINTER__ <= 1
typedef char					intptr_t;
typedef unsigned char			uintptr_t;
#elif	__SIZEOF_POINTER__ <= __SIZEOF_SHORT__
typedef short					intptr_t;
typedef unsigned short			uintptr_t;
#elif	__SIZEOF_POINTER__ <= __SIZEOF_INT__
typedef int					intptr_t;
typedef unsigned int				uintptr_t;
#elif	__SIZEOF_POINTER__ <= __SIZEOF_LONG__
typedef long					intptr_t;
typedef unsigned long			uintptr_t;
#elif	__SIZEOF_POINTER__ <= __SIZEOF_LONG_LONG__
typedef long long				intptr_t;
typedef unsigned long long		uintptr_t;
#endif

#if !defined __cplusplus || defined __STDC_CONSTANT_MACROS

/* Signed.  */
# define INT8_C(c)	c
# define INT16_C(c)	c
# define INT32_C(c)	c
# if __WORDSIZE == 64
#  define INT64_C(c)	c ## L
# else
#  define INT64_C(c)	c ## LL
# endif

/* Unsigned.  */
# define UINT8_C(c)	c
# define UINT16_C(c)	c
# define UINT32_C(c)	c ## U
# if __WORDSIZE == 64
#  define UINT64_C(c)	c ## UL
# else
#  define UINT64_C(c)	c ## ULL
# endif

/* Maximal type.  */
# if __WORDSIZE == 64
#  define INTMAX_C(c)	c ## L
#  define UINTMAX_C(c)	c ## UL
# else
#  define INTMAX_C(c)	c ## LL
#  define UINTMAX_C(c)	c ## ULL
# endif

#endif	/* C++ && constant macros */

#if defined(__WINT_TYPE__)
typedef __WINT_TYPE__ wint_t;
#else
typedef unsigned int wint_t;
#endif
#endif
