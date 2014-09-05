#include <cmdParse.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>



struct KernelConfig GetConfig(int argc, char** args)
{
	int opt;
	
	struct KernelConfig config;

	
	while ((opt = getopt(argc, args, "o:i:")) != -1)
	{
       switch (opt) 
       {
       case 'o': //monitor
           	config.output = optarg;
           	break;
       case 'i':
       		config.input = optarg;
       		break;
       };
 	}
 	
	return config;
}
