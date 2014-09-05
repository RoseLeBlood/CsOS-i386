

#ifndef TYPES_H
#define TYPES_H



#include <klibc/stddef.h>
#include <klibc/stdbool.h>
#include <klibc/stdint.h>
#include <klibc/endian.h>
#include <klibc/limits.h>


        
typedef unsigned int ino_t;
typedef unsigned int dev_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef unsigned int off_t;

typedef unsigned int mode_t;
typedef int ssize_t;

#define HIGHBYTE(w) (BYTE)(((w) >> 8) & 0xFF) //Das oberer BYTE eines WORDs
#define  LOWBYTE(w) (BYTE)((w) & 0xFF)        //Das untere BYTE eines WORDs

#define HIGHWORD(d) (WORD)(((d) >> 16) & 0xFFFF) //Das oberer WORD eines DWORDs
#define  LOWWORD(d) (WORD)((d) & 0xFFFF)        //Das untere WORD eines DWORDs

	

typedef unsigned long       DWORD;
typedef unsigned short      WORD;
typedef unsigned char 	    BYTE;

typedef signed char        CHAR;  //  8-1 Bit
typedef signed short       SHORT; // 16-1 Bit
typedef signed long        INT;   // 32-1 Bit

typedef unsigned char      UCHAR;  //  8 Bit
typedef unsigned short     USHORT; // 16 Bit
typedef unsigned long      UINT;   // 32 Bit

#endif