#include <sys/utsname.h>
#include <string.h>
#include <version.h>
#include <stdio.h>
#include <config.h>

                               
int uname(struct utsname* os_infos)
{ 
  strcpy(os_infos->sysname, NAME);
  strcpy(os_infos->release, RELEASE_NAME);
  strcpy(os_infos->version, VERSION);
  strcpy(os_infos->nodename, NETWORKNAME);
  strcpy(os_infos->machine, MACHINE);
  strcpy(os_infos->cmpversion, itoa(COMPILER_VERSION));
  strcpy(os_infos->cmpname, COMPILER_NAME);
  
  return 0;
}
