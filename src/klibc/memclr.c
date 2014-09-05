#include <math.h>
#include <string.h>

#undef memclr

static void * memclr_std(void * start, size_t count)
{
    asm("rep stosl;"::"a"(0),"D"((size_t)start),"c"(count / 4));
    asm("rep stosb;"::"a"(0),"D"(((size_t)start) + ((count / 4) * 4)),"c"(count - ((count / 4) * 4)));

    return (void *)((size_t)start + count);
}
static void * memclr_sse2(void * start, size_t count)
{
    size_t i;

    if((size_t)start & (SSE_XMM_SIZE - 1))
    {
        i = 0;

        while(((size_t)start + i) & (SSE_XMM_SIZE - 1) && i < count)
        {
            asm("stosb;" :: "D"((size_t)start + i), "a"(0));
            i++;
        }
    }
    else
    {
        i = 0;
    }
 
    for(; i + 64 <= count; i += 64)
    {
        asm volatile(" pxor %%xmm0, %%xmm0;	"  
                     " movdqa %%xmm0, 0(%0);	"    
                     " movdqa %%xmm0, 16(%0);	"
                     " movdqa %%xmm0, 32(%0);	"
                     " movdqa %%xmm0, 48(%0);	"
                     :: "r"((size_t)start + i));
    }
 
    asm(" rep stosb; " :: "a"((size_t)(0)), "D"(((size_t)start) + i), "c"(count - i));

    i += count - i;

    return (void *)(((size_t)start) + i);
}
extern bool CPUID_IsSupport(uint32_t ext);

void * memclr(void * mem, size_t count)
{
    if(!count)
    { 
    	return mem; 
    }
    else if(CPUID_IsSupport(24))
    {
        return memclr_sse2(mem, count);
    }
    return memclr_std(mem, count);
}