#include <Initrdfs.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <devfs.hpp>

initrd_header_t *initrd_header;     // The header.
initrd_file_header_t *file_headers; // The list of file headers.
fs_node_t *initrd_root;             // Our root directory node.
fs_node_t *initrd_dev;              // We also add a directory node for /dev, so we can mount devfs later on.
fs_node_t *initrd_boot; 
fs_node_t *initrd_proc; 

fs_node_t *root_nodes;              // List of file nodes.
uint32_t nroot_nodes;                    // Number of file nodes.

struct dirent dirent;

static uint32_t initrd_read(fs_node_t *node,uint8_t *buffer, uint32_t offset, uint32_t size)
{
    initrd_file_header_t header = file_headers[node->inode];
    if (offset > header.length)
        return 0;
    if (offset+size > header.length)
        size = header.length-offset;
    memcpy(buffer, (uint8_t*) (header.offset+offset), size);
    return size;
}

static struct dirent *initrd_readdir(fs_node_t *node, uint32_t index)
{
    if (node == initrd_root && index == 0)
    {
      strcpy(dirent.name, "dev");
      dirent.name[3] = 0;
      dirent.ino = 0;
      return &dirent;
    }
	
	if (node == initrd_root && index == 1)
    {
      strcpy(dirent.name, "boot");
      dirent.name[4] = 0;
      dirent.ino = 1;
      return &dirent;
    }
    
    if (node == initrd_root && index == 2)
    {
      strcpy(dirent.name, "proc");
      dirent.name[4] = 0;
      dirent.ino = 2;
      return &dirent;
    }
	
    if (index-3 >= nroot_nodes)
        return 0;
    strcpy(dirent.name, root_nodes[index-3].name);
    dirent.name[strlen(root_nodes[index-3].name)] = 0;
    dirent.ino = root_nodes[index-3].inode;
    return &dirent;
}

static fs_node_t *initrd_finddir(fs_node_t *node, char *name)
{
    if (node == initrd_root &&
        !strcmp(name, "dev") )
        return initrd_dev->ptr != NULL ? initrd_dev->ptr : initrd_dev;
	
	if (node == initrd_root &&
        !strcmp(name, "proc") )
        return initrd_proc->ptr != NULL ? initrd_proc->ptr : initrd_proc;
        
    if (node == initrd_root &&
        !strcmp(name, "boot") )
        return initrd_boot->ptr != NULL ? initrd_boot->ptr : initrd_boot;
        
    uint32_t i;
    for (i = 0; i < nroot_nodes; i++)
        if (!strcmp(name, root_nodes[i].name))
            return &root_nodes[i];
    return 0;
}

fs_node_t *initialise_initrd(uint32_t location)
{
    // Initialise the main and file header pointers and populate the root directory.
    initrd_header = (initrd_header_t *)location;
    file_headers = (initrd_file_header_t *) (location+sizeof(initrd_header_t));

    // Initialise the root directory.
    initrd_root = (fs_node_t*)malloc(sizeof(fs_node_t));
    strcpy(initrd_root->name, "initrd");
    initrd_root->mask = initrd_root->uid = initrd_root->gid = initrd_root->inode = initrd_root->length = 0;
    initrd_root->flags = FS_DIRECTORY;
    initrd_root->read = 0;
    initrd_root->write = 0;
    initrd_root->open = 0;
    initrd_root->close = 0;
    initrd_root->readdir = &initrd_readdir;
    initrd_root->finddir = &initrd_finddir;
    initrd_root->ptr = 0;
    initrd_root->impl = 0;

	//initrd_dev = (fs_node_t*)kmalloc(sizeof(fs_node_t));
	//initrd_dev = initialise_devfs();
    // Initialise the /dev directory (required!)
    initrd_dev = (fs_node_t*)malloc(sizeof(fs_node_t));
	strcpy(initrd_dev->name, "dev");
	initrd_dev->mask = initrd_dev->uid = initrd_dev->gid = initrd_dev->inode = initrd_dev->length = 0;
	initrd_dev->flags = FS_DIRECTORY ;
	initrd_dev->read = 0;
	initrd_dev->write = 0;
	initrd_dev->open = 0;
	initrd_dev->close = 0;
	initrd_dev->readdir = &initrd_readdir;
	initrd_dev->finddir = &initrd_finddir;
	initrd_dev->ptr = initialise_devfs();
	initrd_dev->impl = 0;
	
	initrd_boot = (fs_node_t*)malloc(sizeof(fs_node_t));
	strcpy(initrd_dev->name, "boot");
	initrd_boot->mask = initrd_dev->uid = initrd_dev->gid = initrd_dev->inode = initrd_dev->length = 0;
	initrd_boot->flags = FS_DIRECTORY;
	initrd_boot->read = 0;
	initrd_boot->write = 0;
	initrd_boot->open = 0;
	initrd_boot->close = 0;
	initrd_boot->readdir = &initrd_readdir;
	initrd_boot->finddir = &initrd_finddir;
	initrd_boot->ptr = 0;
	initrd_boot->impl = 0;
	
	
	initrd_proc = (fs_node_t*)malloc(sizeof(fs_node_t));
	strcpy(initrd_dev->name, "proc");
	initrd_proc->mask = initrd_dev->uid = initrd_dev->gid = initrd_dev->inode = initrd_dev->length = 0;
	initrd_proc->flags = FS_DIRECTORY;
	initrd_proc->read = 0;
	initrd_proc->write = 0;
	initrd_proc->open = 0;
	initrd_proc->close = 0;
	initrd_proc->readdir = &initrd_readdir;
	initrd_proc->finddir = &initrd_finddir;
	initrd_proc->ptr = 0;
	initrd_proc->impl = 0;
	

    root_nodes = (fs_node_t*)malloc(sizeof(fs_node_t) * initrd_header->nfiles);
    nroot_nodes = initrd_header->nfiles;

    // For every file...
    uint32_t i;
    for (i = 0; i < initrd_header->nfiles ; i++)
    {
        //file_headers[i].offset += location;
        // Create a new file node.
        strcpy(root_nodes[i].name, file_headers[i].name);
        root_nodes[i].mask = root_nodes[i].uid = root_nodes[i].gid = 0;
        root_nodes[i].length = file_headers[i].length;
        root_nodes[i].inode = i;
        root_nodes[i].flags = FS_FILE;
        root_nodes[i].read = &initrd_read;
        root_nodes[i].write = 0;
        root_nodes[i].readdir = 0;
        root_nodes[i].finddir = 0;
        root_nodes[i].open = 0;
        root_nodes[i].close = 0;
        root_nodes[i].impl = 0;
        
    }
    return initrd_root;
}