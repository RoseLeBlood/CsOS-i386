#ifndef DEVFS_H
#define DEVFS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <types.h>
#include <fs.h>

fs_node_t *initialise_devfs();

#ifdef __cplusplus
}
#endif

#endif