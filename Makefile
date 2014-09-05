CFLAGS=-Iinclude/klibc/ -Wall -I.. -I. -Iinclude -Iinclude/klibc/cxx -Wno-write-strings -nostdlib \
		-nostartfiles -ffreestanding  -nostdlib -nostdinc -fno-builtin -m32  \
		-nodefaultlibs -fno-exceptions -Wall -Wextra -fno-leading-underscore \
		-Wno-unused-parameter -Wno-unused-value  -mtune=i686 -mmmx 
  
CXXFLAGS=-lang=c++ -fno-rtti -fuse-cxa-atexit -std=c++11 $(CFLAGS) 

LDFLAGS=-melf_i386 -nostdlib -Tlink.ld
ASFLAGS=-felf32
ISOFLAGS=-R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o bootable.iso isofiles


TCC=gcc
TCP=g++
TAS=as
TLD=ld
TASM=nasm
TISO=genisoimage

OBJS = src/kernel/x86/asm/boot.o \
	   src/kernel/x86/asm/gdt.o \
	   src/kernel/x86/asm/call.o \
	   src/kernel/x86/fpu.o \
	   src/kernel/x86/asm/process.o \
	   src/kernel/x86/gdt.o \
	   src/kernel/x86/isr.o \
	   src/kernel/x86/main.o \
	   src/kernel/x86/cpuid.o \
	   src/cmdParse.o \
	   src/kshell/kshell.o \
	   src/kernel/x86/pmm.o \
	   src/kernel/x86/mm.o

NET =  src/net/network.o  

KLIBC = \
	src/klibc/malloc.o \
	src/klibc/string.o \
	src/klibc/stdio.o \
    src/klibc/time.o \
    src/klibc/typeconv.o \
    src/klibc/assert.o \
    src/klibc/math_exp.o \
    src/klibc/math_misc.o \
    src/klibc/math_pow.o \
    src/klibc/math_trigo.o \
    src/klibc/ctype.o \
    src/klibc/errno.o \
    src/klibc/stdlib.o \
    src/sys/utsname.o \
    src/klibc/libgcc.o \
    src/klibc/iob.o \
    src/klibc/lock.o \
    src/klibc/mm.o \
    src/klibc/memclr.o \
    src/klibc/paddb.o \
    src/klibc/getopt.o \
    src/klibc/getopt_long.o \
    src/klibc/wchar.o\
    src/klibc/wctype.o \
    src/klibc/atomic.o \
    src/klibc/_extern.o \
    src/sys/sthread.o
        
KLIBCPP = src/klibc/cxx/new.o \
		  src/klibc/cxx/icxxabi.o \
		  src/klibc/cxx/cxxstd.o \
		  src/klibc/cxx/list.o \
		  src/klibc/cxx/iostream.o \
		  src/klibc/cxx/intrusive_list.o \
		  src/klibc/cxx/intrusive_slist.o \
		  src/klibc/cxx/slist.o \
		  src/IStream.o \
		  src/klibc/cxx/lock.o

FS	  = src/fs.o src/Initrdfs.o \
		src/DeviceStream.o \
		src/devfs.o

DEV   = src/dev/Driver.o \
	    src/dev/DriverList.o \
	    src/dev/Device.o \
	    src/dev/timer.o \
	    src/dev/cga_out.o \
	    src/dev/serial_out.o \
	    src/dev/DeviceList.o \
	    src/dev/key_input.o \
	    src/dev/random.o \
	    src/dev/bus/PciBus.o \
	    src/dev/bus/pci_list.o \
	    src/dev/bus/pci_entry.o \
	    src/dev/dma.o \
	    src/dev/net/rtl8139.o


COM_O = $(KLIBC) $(KLIBCPP) $(DEV) $(FS) $(NET)
COM_1 = $(KLIBC) $(KLIBCPP)


INITRDFILES = include/version.h initrd/config.cfg

KERNEL=kernel86.bin
INITRD=make_initrd.bin

PROMPT = " -> "
AR = @echo "   " $(PROMPT)  AR "    " $ && ar
CD = @echo  $(PROMPT) CD "        " && cd
LD = @echo "   " $(PROMPT) LIN "    " $ && $(TLD)
CC = @echo "   " $(PROMPT) GCC "   " $< && $(TCC)
CPP = @echo "   " $(PROMPT) GPP "   " $< && $(TCP)
ASM = @echo "   " $(PROMPT) ASM "   " $< && $(TASM)
AS = @echo "   " $(PROMPT) AS "   " $< && $(TAS)
RM = @echo "   " $(PROMPT) REM "   " $< && rm
CP = @echo "   " $(PROMPT)  CP && cp


SOURCES=$(OBJS) $(COM_O)

all: $(SOURCES) link
.s.o:
	$(ASM) $(ASFLAGS) $<
.c.o:
	$(CC) $(CFLAGS) -std=gnu99 -c $< -o $@
.cpp.o:
	$(CPP) $(CXXFLAGS) -c $< -o $@
link:
	$(LD) $(LDFLAGS) -o $(KERNEL) $(SOURCES)
	readelf -a kernel86.bin > kernel.txt
	$(TCP) initrd/make_initrd.cpp -m32 -march=i686 -std=c++11 -o $(INITRD) 
	./$(INITRD)  $(INITRDFILES)
	cp kernel86.bin isofiles/boot/kernel.bin
	cp initrd.mod isofiles/boot/initrd.mod
	$(TISO) $(ISOFLAGS) 2>>/dev/null
test:
	#/usr/lib/virtualbox/VirtualBox --comment "CSOS" --startvm "0318b762-3710-462a-baaa-e5703e063e47"
	qemu -cdrom bootable.iso -m 32 -serial file:serial.out -net nic,model=rtl8139 -net user
bclean:
	$(RM) $(SOURCES) $(INITRD) $(KERNEL)
clean:
	$(RM) $(SOURCES) $(INITRD) $(KERNEL) initrd.mod bootable.iso
