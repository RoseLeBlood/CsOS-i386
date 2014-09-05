#include <kernel/kernel.hpp>
#include <cxx/stl.hpp>
#include <cxx/iostream.hpp>
#include <time.h>
#include <dev/timer.hpp>
#include <sleep.h>
#include <string.h>
#include <Initrdfs.h>
#include <stdio.h>
#include <malloc.h>
#include <kernel/cpuid.hpp>
#include <kernel/fpu.hpp>
#include <cmdParse.h>
#include <kernel/mm.h>

uint32_t initrd_location, initrd_end;


void* kernel_instance;
uint32_t initial_esp;

extern "C" void kernel_shell();
extern "C" bool sthread_init();


Kernel::Kernel(multiboot_info_t *mpt) : m_multibootptr(mpt)
{
	m_driverList = new dev::DriverList();
	
}

int Kernel::RunKernel(int args, char** argv)
{   
	m_devices = new dev::DeviceManager();
	m_devices->ProbeAll();
	
	KernelConfig cfg = GetConfig(args, argv);
  	std::cout.SetDevice(cfg.output);
  	std::cin.SetDevice("kb0");
  	
	fs_root = initialise_initrd(initrd_location);
	
	sthread_init();
	kernel_shell();
	
	return 0;
}


int main(multiboot_info_t *mboot_ptr, uint32_t initial_stack)
{
    initial_esp = initial_stack;
    gdt_install();
	CPUID::parse();
	init_fpu();
	init_sse();
	
	
    asm volatile("sti");

  	  
  	assert(mboot_ptr->mods_count > 0);
    initrd_location = *((uint32_t*)mboot_ptr->mods_addr);
    initrd_end = *(uint32_t*)(mboot_ptr->mods_addr+4);
    //placement_address = initrd_end;
    
    uint32_t mem = mboot_ptr->mem_lower + mboot_ptr->mem_upper;
    mm_init(mem);
    
    //paging_install();
    
	kernel_instance = new Kernel(mboot_ptr);
	
	// split string cmd
	uint32_t s = 0;
    char** cmd = make_args((char*)mboot_ptr->cmdline, &s);		
    return ((Kernel*)kernel_instance)->RunKernel(s, cmd);
}

