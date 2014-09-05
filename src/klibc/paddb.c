#include <math.h>
#include <string.h>

void paddb(uint8_t DST[16], const uint8_t v2[16])
{
    uint8_t SRC[16] __attribute__((aligned(16)));

    if((size_t)SRC & (SSE_XMM_SIZE - 1))
    { 
    	memcpy(SRC, v2, 16); 
    }

    asm(" movdqu (%0), %%xmm1;   "  
        " paddb (%1), %%xmm1;    "   
        " movdqu %%xmm1, (%0);   "   
        :: "r"((size_t)DST), "r"((size_t)SRC));
}

void paddw(uint16_t DST[8], const uint16_t v2[8])
{
    uint16_t SRC[8] __attribute__((aligned(16)));

    if((size_t)SRC & (SSE_XMM_SIZE - 1))
    {
     	memcpy(SRC, v2, 16); 
     }

    asm(" movdqu (%0), %%xmm1;   "   
        " paddw (%1), %%xmm1;    "   
        " movdqu %%xmm1, (%0);   "   
        :: "r"((size_t)DST), "r"((size_t)SRC));
}
void paddd(uint32_t DST[4], const uint32_t v2[4])
{
    uint32_t SRC[4] __attribute__((aligned(16)));

    if((size_t)SRC & (SSE_XMM_SIZE - 1))
    { 
    	memcpy(SRC, v2, 16); 
    }

    asm(" movdqu (%0), %%xmm1;   "  
        " paddd (%1), %%xmm1;    "   
        " movdqu %%xmm1, (%0);   "  
        :: "r"((size_t)DST), "r"((size_t)SRC));
}
void paddq(uint64_t DST[2], const uint64_t v2[2])
{
    // we need an aligned buffer, just in case
    uint64_t SRC[2] __attribute__((aligned(16)));

    // if SRC is not aligned, we need to copy those values into our temp buffer
    if((size_t)SRC & (SSE_XMM_SIZE - 1))
    { 
    	memcpy(SRC, v2, 16); 
    }

    // if SRC is not aligned, PADDB will GPF
    asm(" movdqu (%0), %%xmm1;   "   // move DST into XMM1
        " paddq (%1), %%xmm1;    "   // add DST+SRC into XMM1
        " movdqu %%xmm1, (%0);   "   // store XMM1 into DST
        :: "r"((size_t)DST), "r"((size_t)SRC));
}
