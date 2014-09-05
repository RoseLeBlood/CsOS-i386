CFLAGS=-Iinclude/klibc/ -Wall -I.. -I. -Iinclude -Iinclude/klibc/cxx -Wno-write-strings -nostdlib \
		-nostartfiles -ffreestanding -fno-stack-protector -nostdlib -nostdinc -fno-builtin -m32 -march=i686 \
		-nodefaultlibs -fno-exceptions -Wall -Wextra -fno-leading-underscore \
		-Wno-unused-parameter -Wno-unused-value
		
		
		
  
	    
	  
CXXFLAGS=-lang=c++ -fno-rtti -fuse-cxa-atexit -std=c++11 $(CFLAGS)

LDFLAGS=-melf_i386 -nostdlib -Tsrc/arch/x86/link.ld
ASFLAGS=-felf32
ISOFLAGS=-R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o bootable.iso isofiles

TCC=gcc
TCP=g++
TAS=as
TLD=ld
TASM=nasm
TISO=genisoimage

OBJS =  \
	src/arch/x86/arch.o \
	src/arch/x86/boot.o \
	src/arch/x86/calls.o \
	src/arch/x86/clock.o \
	src/arch/x86/cpu.o \
	src/arch/x86/idt.o \
	src/arch/x86/isr.o \
	src/arch/x86/gdt.o \
	src/arch/x86/irq.o \
	src/arch/x86/io.o \
	src/arch/x86/kkeyb.o \
	src/arch/x86/kvideo.o \
	src/arch/x86/timer.o \
	src/arch/x86/fpu.o \
	src/kernel.o \
	src/arch/x86/icxxabi.o \
	src/kshell.o

KLIBC = \
	src/klibc/malloc.o \
	src/klibc/stdio.o \
	src/klibc/string.o \
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
    src/klibc/libgcc.o 
        
KLIBCPP = src/klibc/cxx/iostream.o \
		  src/klibc/cxx/new.o

MEM	  = src/mm/phys.o \
		src/mm/mm.o \
		src/mm/pmm.o

DEV   = src/dev/Driver.o \
		src/dev/DriverList.o \
		src/dev/hid/Mouse.o \
		src/dev/Device.o \
		src/dev/audio/pcspk.o

COM_O = $(KLIBC) $(KLIBCPP) $(MEM) $(DEV)

#src/Main.o src/Driver.o src/Term.o src/Device.o src/ArchManager.o src/DeviceManager.o src/DriverManager.o \
#src/Task.o src/TaskManager.o 


PROMPT = " -> "
AR = @echo "   " $(PROMPT)  AR "    " $ && ar
CD = @echo  $(PROMPT) CD "        " && cd
LD = @echo "   " $(PROMPT) LIN "    " $ && $(TLD)
CC = @echo "   " $(PROMPT) GCC "   " $< && $(TCC)
CPP = @echo "   " $(PROMPT) GPP "   " $< && $(TCP)
ASM = @echo "   " $(PROMPT) ASM "   " $< && $(TASM)
AS = @echo "   " $(PROMPT) AS "   " $< && $(TAS)
RM = @echo "   " $(PROMPT) REM "   " $< && rm
IS = @echo "   " $(PROMPT) ISO "   " $ && $(TISO)
CP = @echo "   " $ && cp

KERNEL=kernel86.bin

SOURCES=$(OBJS) $(COM_O)

all: $(SOURCES) link
.s.o:
	$(ASM) $(ASFLAGS) $<
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
.cpp.o:
	$(CPP) $(CXXFLAGS) -c $< -o $@
link:
	$(LD) $(LDFLAGS) -o $(KERNEL) $(SOURCES)
iso:
	$(CP) kernel86.bin isofiles/boot/kernel.bin
	$(IS) $(ISOFLAGS) 2>>/dev/null
test:
	/usr/lib/virtualbox/VirtualBox --comment "CSOS" --startvm "0318b762-3710-462a-baaa-e5703e063e47"
clean:
	$(RM) $(SOURCES)
drivers: $(MODULES)
	$(CP) $(MODULES) ../drivers/
