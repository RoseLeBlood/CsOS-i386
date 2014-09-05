#include <sys/sthread.h>
#include <malloc.h>
#include <string.h>
#include <mmalloc.h>
#include <kernel/isr.h>
#include <assert.h>
#include <atomic.h>

/*#define STHREAD_NULL			0
#define STHREAD_PAUSED 			1
#define STHREAD_CANKILL			2
#define STHREAD_STOPPED			3
#define STHREAD_READY			4*/

struct sthread_struct
{
	sthread_t thread;
	sthreadrun_t entry;
	
	struct sthread_struct *next;
};

struct sthread_struct *sthread_root = NULL;
struct sthread_struct *sthread_current = NULL;



void sthreadSwitch()  
{
	if(sthread_current != NULL)
	{
		if(sthread_current->next != NULL)
		{
			sthread_current->thread.status = STHREAD_PAUSED;
			sthread_current = sthread_current->next;
			sthread_current->thread.status = STHREAD_RUN;
		}
		else
		{
			sthread_current->thread.status = STHREAD_PAUSED;
			sthread_current = sthread_root;
		}
	
	}
}
void sthreadRun()
{
	if(sthread_current != NULL)
	{
		sthread_current->entry(NULL);
	
	}
}
int sthread_nextpid()
{
	static int ids;
	return ids++;
}

int		sthread_create(const char name[32], sthreadrun_t entry)
{
	int id = sthread_nextpid();
	
	//asm volatile("cli");

    /*sthread_t *task = (sthread_t*) malloc(sizeof(sthread_t));
    strncpy(task->name, name, strlen(name));
    
	task->pid = id;
	task->status = STHREAD_READY;
	task->thread = thread;

    

    threads[id] = *task;
    pid = id;

    asm volatile("sti");  */                                                     // allow Interrupts again*/
	//return &threads[id];
	return id;
}

void				 	sthread_send(int id, int signal)
{
	//assert(id < 100);	
	//threads[id].signal = signal;
}
void					sthread_destroy(int id)
{
	//if(id == 0)
	//	return;
	//threads[id].status = STHREAD_KILL;
}

void idle_task()
{
	//for(int id=0; id < 100; id++)
	//{
	//	if(threads[id].status == STHREAD_KILL)
	//	{
	//		threads[id].pid = -1;
	//		threads[id].status = STHREAD_EMPTY;
	//		threads[id].thread = NULL;
	//		strncpy(threads[id].name, "", strlen(""));
	//	}
	//}
}
bool sthread_init()
{
	return true;
	//return sthread_create(1, "idle", &idle_task) != NULL;
}