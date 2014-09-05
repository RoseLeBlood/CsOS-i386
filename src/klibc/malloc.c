#include <klibc/ctype.h>
#include <klibc/malloc.h>
#include <klibc/string.h>
#include <kernel/mm.h>

uint32_t allocindex;


/* alloc and full with zeros */
void *calloc(size_t size2, size_t size)
{
        size_t x;
        char *adr = (char *) mm_alloc(size);
        char *j = adr;

        for(x = 0; x < size; x++)
        {
                *j = 0;
                j++;
        }
        return (void *) adr;
}


/* alloc */
void *malloc(size_t size)
{
       allocindex++;

        return (void *) mm_alloc(size);
}


/* realloc */
void *realloc(void *adr, size_t size)
{
        void *new = (void *) mm_alloc(size);
        memcpy(new, adr, size);
        //free(adr);

        return (void *) new;
}


/* free memory */
void free(void *adr)
{
        allocindex--;
        
        mm_free(adr);
}
