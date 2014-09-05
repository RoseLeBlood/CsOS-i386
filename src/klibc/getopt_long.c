#include <getopt.h>


#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define __P(x) x
#define _DIAGASSERT(x) assert(x)

#define	BADCH	(int)'?'
#define	BADARG	(int)':'
#define	EMSG	""
		
int getopt_internal(nargc, nargv, ostr)
	int nargc;
	char * const *nargv;
	const char *ostr;
{
	static char *place = EMSG;		
	char *oli;			

	assert(nargv != NULL);
	assert(ostr != NULL);

	if (optreset || !*place) 
	{		
		optreset = 0;
		if (optind >= nargc || *(place = nargv[optind]) != '-') 
		{
			place = EMSG;
			return (-1);
		}
		if (place[1] && *++place == '-') 
		{	
			place = EMSG;
			return (-2);
		}
	}					
	if ((optopt = (int)*place++) == (int)':' || !(oli = strchr(ostr, optopt))) 
	{
		if (optopt == (int)'-')
			return (-1);
		if (!*place)
			++optind;
		
		return (BADCH);
	}
	if (*++oli != ':') 
	{			
		optarg = NULL;
		if (!*place)
			++optind;
	} 
	else 
	{				
		if (*place)			
			optarg = place;
		else if (nargc <= ++optind) 
		{	
			place = EMSG;
			return (BADARG);
		} 
		else				
			optarg = nargv[optind];
		place = EMSG;
		++optind;
	}
	return (optopt);			
}

int getopt_long(nargc, nargv, options, long_options, index)
	int nargc;
	char ** nargv;
	char * options;
	struct option * long_options;
	int * index;
{
	int retval;

	assert(nargv != NULL);
	assert(options != NULL);
	assert(long_options != NULL);
	/* index may be NULL */

	if ((retval = getopt_internal(nargc, nargv, options)) == -2) 
	{
		char *current_argv = nargv[optind++] + 2, *has_equal;
		int i, current_argv_len, match = -1;

		if (*current_argv == '\0') 
		{
			return(-1);
		}
		if ((has_equal = strchr(current_argv, '=')) != NULL) 
		{
			current_argv_len = has_equal - current_argv;
			has_equal++;
		} 
		else
			current_argv_len = strlen(current_argv);

		for (i = 0; long_options[i].name; i++) 
		{ 
			if (strncmp(current_argv, long_options[i].name, current_argv_len))
				continue;

			if (strlen(long_options[i].name) == (unsigned)current_argv_len) 
			{ 
				match = i;
				break;
			}
			if (match == -1)
				match = i;
		}
		if (match != -1) 
		{
			if (long_options[match].has_arg == required_argument ||
			    long_options[match].has_arg == optional_argument) 
			{
				if (has_equal)
					optarg = has_equal;
				else
					optarg = nargv[optind++];
			}
			if ((long_options[match].has_arg == required_argument) && (optarg == NULL)) 
			{
				return (BADARG);
			}
		} 
		else 
		{
			return (BADCH);
		}
		if (long_options[match].flag)
		{
			*long_options[match].flag = long_options[match].val;
			retval = 0;
		} 
		else 
			retval = long_options[match].val;
		if (index)
			*index = match;
	}
	return(retval);
}















