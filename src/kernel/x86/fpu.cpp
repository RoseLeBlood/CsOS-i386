#include <stddef.h>
#include <kernel/cpuid.hpp>
#include <kernel/fpu.hpp>

uint16_t FPU_CW;

void init_fpu(void)
{
    /* FINIT = FPU INIT.  This allows for the use of Float/Double/Long Double data types */
    if(CPUID::IsSupport(cpuid::FPU)) 
    {
        asm volatile("finit;                    "
                                         "fstcw (%1);           "
                                         "mov %0, (%1);         "
                                         "fldcw (%1);           "
                                         ::"r"(0xB7F), "r"(&FPU_CW));     
    }
}

void init_sse(void)
{
    size_t cr0, cr4;
    
    /* Set MP, OSFXSR, and OSXMMEXCPY, and disable EM (FPU emulation) */
    if(CPUID::IsSupport(cpuid::FPU) && CPUID::IsSupport(cpuid::SSE) | CPUID::IsSupport(cpuid::SSE2)) 
    {
        asm volatile("mov %%cr0, %0;":"=r"(cr0)); /* store CR0 */
        asm volatile("mov %%cr4, %0;":"=r"(cr4)); /* store CR4 */
        
        cr0 &= ~CR0_EM; /* disable FPU emulation */
        cr0 |= CR0_MP;  /* set MP bit */
        cr4 |= (CR4_OSFXSR | CR4_OSXMMEXCPT); /* set the bits to enable FPU SAVE/RESTORE and XMM registers */
        
        asm volatile("mov %0, %%cr4;"::"r"(cr4)); /* restore CR4 */
        asm volatile("mov %0, %%cr0;"::"r"(cr0)); /* restore CR0 */
    }  
    
    init_fpu(); 
}
