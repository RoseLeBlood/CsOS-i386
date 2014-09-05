#ifndef __STD_ENDIAN_H__
#define __STD_ENDIAN_H__

#define	__LITTLE_ENDIAN	1234
#define	__BIG_ENDIAN	4321

#define __BYTE_ORDER		__LITTLE_ENDIAN
#define __FLOAT_WORD_ORDER	__BYTE_ORDER

#if __BYTE_ORDER == __LITTLE_ENDIAN
# define __LONG_LONG_PAIR(HI, LO) LO, HI
#elif __BYTE_ORDER == __BIG_ENDIAN
# define __LONG_LONG_PAIR(HI, LO) HI, LO
#endif

#define __WORDSIZE 32


#endif