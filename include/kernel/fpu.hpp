#ifndef FPU_H
#define FPU_H

#ifdef	__cplusplus
extern "C" {
#endif
#define FPU_CTRL_RW                     10

#define FPU_CTRL_RW_NEAREST     0x00
#define FPU_CTRL_RW_DOWN        0x01
#define FPU_CTRL_RW_UP          0x02
#define FPU_CTRL_RW_TRUNC       0x03

#define CR0_EM          (1 << 2)
#define CR0_MP          (1 << 1)
#define CR4_OSFXSR      (1 << 9)
#define CR4_OSXMMEXCPT  (1 << 10)

extern uint16_t FPU_CW;

void init_fpu(void);
void set_fpu(const uint16_t CW);
void init_sse(void);

#ifdef	__cplusplus
}
#endif
#endif
