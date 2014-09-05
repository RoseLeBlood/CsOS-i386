phys = 0x00100000;

SECTIONS
{
	. = phys;
	_kernel_start = phys;
	
	.mboot  : AT ( ADDR( .mboot ) ) 
	{
		*(multiboot*)
	}
	.text  ALIGN(4096) : AT(ADDR(.text))
	{
		code = .;
		*(.text*)
		*(.gnu.linkonce.t*)
		
	}
	.rodata ALIGN(4096) : AT(ADDR(.rodata))
	{
		rodata = .;
		*(.rodata*)
		*(.gnu.linkonce.r.*)
		_ro_end = .;
	}
	
	.data ALIGN(4096) : AT(ADDR(.text) + (data - code)) 
	{
		data = .;
		*(.data*)
		*(.gnu.linkonce.d*)
	}
	.ctors ALIGN(4096) : AT(ADDR(.text) + (start_ctors - code))
	{
		start_ctors = .;
		KEEP(*(SORT(.ctors.*)))
		KEEP(*(.ctors))
		end_ctors = .;
	}
	.dtors ALIGN(4096) : AT(ADDR(.text) + (start_dtors - code))
	{
		start_dtors = .;            
		KEEP(*(SORT(.dtors.*)))
		KEEP(*(.dtors))
		end_dtors = .;
	}
	.bss ALIGN(4096) : AT(ADDR(.text) + (bss - code)) 
	{ 	
		bss = .;
		
		*(.COMMON*)
		*(.bss*)
		*(.gnu.linkonce.b*)
	}
	 /DISCARD/ :
	 {
	 	*(.fini_array*)
		*(.comment)
		*(.eh_frame) /* You should discard this unless you're implementing runtime support for C++ exceptions. */
	 }
	 
	 
	 _kernel_end = .;
}
