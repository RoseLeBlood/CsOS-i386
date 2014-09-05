#include <devfs.hpp>
#include <kernel/kernel.hpp>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include <dev/DeviceList.hpp>

fs_node_t *dev_root;
fs_node_t *dev_root_nodes; 
uint32_t dev_nroot_node;
struct dirent dirent;

extern "C"  uint32_t devfs_read(fs_node_t *node,uint8_t *buffer, uint32_t offset, uint32_t size)
{
    return 0;
}

extern "C"  struct dirent *devfs_readdir(fs_node_t *node, uint32_t index)
{
	if (node == dev_root && index == 0)
    {
      strcpy(dirent.name, "dev");
      dirent.name[3] = 0;
      dirent.ino = 0;
      return &dirent;
    }
    if (index-1 >= dev_nroot_node)
        return 0;
    strcpy(dirent.name, dev_root_nodes[index-1].name);
    dirent.name[strlen(dev_root_nodes[index-1].name)] = 0;
    dirent.ino = dev_root_nodes[index-1].inode;
    return &dirent;
}

extern "C"  fs_node_t *devfs_finddir(fs_node_t *node, char *name)
{ 
    uint32_t i;
    for (i = 0; i < dev_nroot_node; i++)
    {
    	
        if (!strcmp(name, dev_root_nodes[i].name))
            return &dev_root_nodes[i];
    }
            
    return 0;
}


extern "C" fs_node_t *initialise_devfs()
{
	dev_root = (fs_node_t*)malloc(sizeof(fs_node_t));
    strcpy(dev_root->name, "dev");
    dev_root->mask = dev_root->uid = dev_root->gid = dev_root->inode = dev_root->length = 0;
    dev_root->flags = FS_DIRECTORY;
    dev_root->read = 0;
    dev_root->write = 0;
    dev_root->open = 0;
    dev_root->close = 0;
    dev_root->readdir = &devfs_readdir;
    dev_root->finddir = &devfs_finddir;
    dev_root->ptr = 0;
    dev_root->impl = 0;

	std::list<DeviceStream*> *devs = Kernel::Instance().GetDevices()->getList();
	dev_nroot_node = devs->size(); 
	dev_root_nodes = (fs_node_t*)malloc(sizeof(fs_node_t) * devs->size());

	uint32_t o = 0;
	for(std::list<DeviceStream*>::iterator i = devs->begin(); i != devs->end(); i++)
	{
		strcpy(dev_root_nodes[o].name, (*i)->getName());
        dev_root_nodes[o].mask = dev_root_nodes[o].uid = dev_root_nodes[o].gid = 0;
        dev_root_nodes[o].length = 1;
        dev_root_nodes[o].inode = o;
        dev_root_nodes[o].flags = FS_FILE;
        dev_root_nodes[o].read = &devfs_read;
        dev_root_nodes[o].write = 0;
        dev_root_nodes[o].readdir = 0;
        dev_root_nodes[o].finddir = 0;
        dev_root_nodes[o].open = 0;
        dev_root_nodes[o].close = 0;
        dev_root_nodes[o].impl = 0;
        
        o++;
	}
	return dev_root;
}