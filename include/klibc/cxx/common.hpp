#ifndef _STD_COMMON_H_
#define _STD_COMMON_H_


#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>		
#include <limits.h>
#include <float.h>
#include <sys/unistd.h>
#include <wchar.h>

 
namespace std 
{ 
        namespace Sys 
        {
                inline void MemCpy(void* to, const void* from, size_t bytes)
                {
                        memcpy(to, from, bytes);
                }
                inline void MemMove(void* to, const void* from, size_t bytes)
                {
                        memmove(to, from, bytes);
                }
                inline void MemSet(void* buf, unsigned char value, size_t bytes)
                {
                        memset(buf, value, bytes);
                }
                
                inline void wMemCpy(void* to, const void* from, size_t bytes)
                {
                        wmemcpy((wchar_t*)to, (wchar_t*)from, bytes);
                }
                inline void wMemMove(void* to, const void* from, size_t bytes)
                {
                        wmemmove((wchar_t*)to, (wchar_t*)from, bytes);
                }
                inline void wMemSet(void* buf, unsigned char value, size_t bytes)
                {
                        wmemset((wchar_t*)buf, value, bytes);
                }
        } 
}

namespace std
{
	enum e_noinitialize
	{
	        noinitialize
	};
}

#endif
