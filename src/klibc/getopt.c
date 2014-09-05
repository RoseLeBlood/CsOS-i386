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

int	opterr = 1, optind = 1,	 optopt, optreset;		
char*optarg;		

static char * _progname __P((char *));
int getopt_internal __P((int, char * const *, const char *));

static char *_progname(nargv0) char * nargv0;
{
	char * tmp;
	assert(nargv0 != NULL);

	tmp = strrchr(nargv0, '/');
	if (tmp) tmp++;
	else tmp = nargv0;
	return(tmp);
}

int getopt(nargc, nargv, ostr)
	int nargc;
	char *  nargv[];
	char *ostr;
{
	static char *__progname = 0;
	static char *place = EMSG;		
	char *oli;				
   	__progname = __progname?__progname:_progname(*nargv);

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
		if (place[1] && *++place == '-' && place[1] == '\0') 
		{
			++optind;
			place = EMSG;
			return (-1);
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
			if (*ostr == ':')
				return (BADARG);
			
			return (BADCH);
		}
	 	else			
			optarg = nargv[optind];
		place = EMSG;
		++optind;
	}
	return (optopt);			
}
