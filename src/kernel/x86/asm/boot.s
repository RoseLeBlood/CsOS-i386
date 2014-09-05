section .mboot

MBOOT_PAGE_ALIGN    equ 1<<0    ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO      equ 1<<1    ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ; Multiboot Magic value
; NOTE: We do not use MBOOT_AOUT_KLUDGE. It means that GRUB does not
; pass us a symbol table.
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)


[BITS 32]                       ; All instructions should be 32-bit.



section .mboot
[GLOBAL mboot]                  ; Make 'mboot' accessible from C.
[EXTERN code]                   ; Start of the '.text' section.
[EXTERN bss]                    ; Start of the .bss section.
[EXTERN _kernel_end]                    ; End of the last loadable section.
multiboot:
    dd  MBOOT_HEADER_MAGIC      ; GRUB will search for this value on each
                                ; 4-byte boundary in your kernel file
    dd  MBOOT_HEADER_FLAGS      ; How GRUB should load your file / settings
    dd  MBOOT_CHECKSUM          ; To ensure that the above values are correct
    
    dd  multiboot                   ; Location of this descriptor
    dd  code                    ; Start of kernel '.text' (code) section.
    dd  bss                     ; End of kernel '.data' section.
    dd  _kernel_end                     ; End of kernel.
    dd  start                   ; Kernel entry point (initial EIP).

section .text
[GLOBAL start]                  ; Kernel entry point.
[EXTERN main]                   ; This is the entry point of our C code
[EXTERN initialiseConstructors]

start:
    ; Load multiboot information:
    push esp
    push ebx

    ; Execute the kernel:
    cli                         ; Disable interrupts.
    call initialiseConstructors ;
    call main                   ; call our main() function.
    jmp $                       ; Enter an infinite loop, to stop the processor
                                ; executing whatever rubbish is in the memory
                                ; after our kernel!
