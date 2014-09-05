#ifndef SYS_UTSNAME_H
#define SYS_UTSNAME_H

#ifdef __cplusplus
extern "C"
{
#endif


#define SYS_LEN 257

struct utsname 
{
  	char  sysname[SYS_LEN];
  	char  nodename[SYS_LEN];
                 
  	char  release[SYS_LEN];
  	char  version[SYS_LEN];
  	char  machine[SYS_LEN];
  	
  	char  cmpversion[SYS_LEN];
  	char  cmpname[SYS_LEN];
};

int uname(struct utsname*);

#ifdef __cplusplus
}
#endif

#endif