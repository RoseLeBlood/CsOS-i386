#ifndef MM_H
#define MM_H

#ifdef __cplusplus
extern "C" 
{
#endif

#include <types.h>

int 				mm_init(uint64_t);
void 				mm_test();
void 				mm_free(void *);
intptr_t*			mm_alloc(size_t);
uint32_t 			mm_get_total_mem();
uint32_t 			mm_get_used_mem();
uint32_t 			mm_get_usable_size(void *);
void 				show_used_memory();

#ifdef __cplusplus
};
#endif

#endif
