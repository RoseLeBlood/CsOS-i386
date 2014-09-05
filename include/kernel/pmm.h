#ifndef KHEAP_H
#define KHEAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>
#include <iob.h>


#define PHYS_MAX_PAGE   1048576                                 
#define PHYS_PAGE_SIZE  4                                               
#define PHYS_MAX_BLOCKS (PHYS_MAX_PAGE / 32)    

typedef struct
{
        void *address;         
        size_t dim;                   
} pmm_page_t;


                                               

void 						pmm_reserve(uint32_t, uint32_t);
void 						pmm_free(void *);
intptr_t*					pmm_alloc(size_t);
void 						pmm_init(uint32_t);
uint8_t 					pmm_if_free_page(int *, int *);
uint32_t 					pmm_get_free_pages();
uint32_t 					pmm_first_free_alloc();

#ifdef __cplusplus
}
#endif

#endif // KHEAP_H