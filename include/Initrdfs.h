#ifndef INITRD_H
#define INITRD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <types.h>
#include <fs.h>

typedef struct
{

	unsigned char magic;
	char name[64];
	unsigned int offset;
	unsigned int length;
	
	
}initrd_file_header_t;

typedef struct
{
    uint32_t nfiles; // The number of files in the ramdisk.
} initrd_header_t;


// Initialises the initial ramdisk. It gets passed the address of the multiboot module,
// and returns a completed filesystem node.
fs_node_t *initialise_initrd(uint32_t location);

#ifdef __cplusplus
}
#endif

#endif
