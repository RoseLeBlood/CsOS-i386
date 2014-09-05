#ifndef SYS_STAT_H
#define SYS_STAT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <types.h>

struct stat 
{
        dev_t st_dev; 
        uid_t st_uid;       
        gid_t st_gid; 
        off_t st_size; 
};


int stat(const char *, struct stat *);

#ifdef __cplusplus
}
#endif
