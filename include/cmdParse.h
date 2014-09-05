#ifndef __CMD_LINE_KERNEL_PARSER
#define __CMD_LINE_KERNEL_PARSER

#ifdef __cplusplus
extern "C"
{
#endif

#include <types.h>

struct KernelConfig
{
	char *output;
	char *input;
};


struct KernelConfig GetConfig(int argc, char** args);

#ifdef __cplusplus
}
#endif

#endif