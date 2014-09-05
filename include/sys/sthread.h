#ifndef SYS_STHREAD_H
#define SYS_STHREAD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <types.h>
#include <stddef.h>


#define STHREAD_NULL			0
#define STHREAD_PAUSED 			1
#define STHREAD_CANKILL			2
#define STHREAD_STOPPED			3
#define STHREAD_READY			4
#define STHREAD_RUN				5

#include <kernel/isr.h>



typedef struct
{
	uint32_t 	tid;         
	uint32_t 	status;
	uint32_t	signal;
	char 		name[32];   
}sthread_t;

typedef void (*sthreadrun_t)(void*);

int	    				sthread_create(const char name[32], sthreadrun_t entry);
void				 	sthread_send(int id, int signal);
void					sthread_destroy(int id);

int 					sthread_nextpid();


#ifdef __cplusplus
}
#endif

#endif
