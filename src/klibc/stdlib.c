#include <stdlib.h>
#include <ctype.h>

static unsigned long _rand_value = 1;

double                          atof            (const char* nptr);




int atoi(const char* str) 
{
        int result = 0;
        while (isspace(*str))
                str++;
        while (isdigit(*str))
                result = (result * 10) + (*(str++) - '0');
        return result;
}

long int atol(const char* str) 
{
        long int result = 0;
        while (isspace(*str))
                str++;
        while (isdigit(*str))
                result = (result * 10) + (*(str++) - '0');
        return result;
}

long long int atoll(const char* str) 
{
        long long int result = 0;
        while (isspace(*str))
                str++;
        while (isdigit(*str))
                result = (result * 10) + (*(str++) - '0');
        return result;
}

double                          strtod  (const char* nptr, char** endptr);
float                                   strtof          (const char* nptr, char** endptr);
long double                     strtold (const char* nptr, char** endptr);
long int                                strtol          (const char* nptr, char** endptr, int base);
long long int                   strtoll (const char* nptr, char** endptr, int base);
unsigned long int               strtoul (const char* nptr, char** endptr, int base);
unsigned long long int  strtoull        (const char* nptr, char** endptr, int base);

int rand() 
{
        _rand_value = _rand_value * 110351524 + 12345;
        return (_rand_value % (RAND_MAX + 1));
}

void srand(unsigned int seed) 
{
        _rand_value = seed;
}

void*                           bsearch (const void* key, const void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));
void                                    qsort           (void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

int abs(int j) 
{
        return (j < 0) ? (-j) : j;
}

long int labs(long int j) 
{
        return (j < 0) ? (-j) : j;
}

long long int llabs(long long int j) 
{
        return (j < 0) ? (-j) : j;
}

div_t div(int numer, int denom) 
{
        div_t result;
        result.quot = numer / denom;
        result.rem = numer % denom;
        return result;
}

ldiv_t ldiv(long int numer, long int denom) 
{
        ldiv_t result;
        result.quot = numer / denom;
        result.rem = numer % denom;
        return result;
}

lldiv_t lldiv(long long int numer, long long int denom) 
{
        lldiv_t result;
        return result;
}

int mblen(const char *s, size_t n)
{
      if (s == (const char *)NULL) return 0;
      if (n <= 0) return 0;
      return (*s != 0);
}
int mbtowc(wchar_t *pwc, register const char *s, size_t n)
{
	  if (s == (const char *)NULL) return 0;
	  if (n <= 0) return 0;
	  if (pwc) *pwc = *s;
	  return (*s != 0);
}
int wctomb  (char* s, wchar_t wchar)
{
	if (!s) return 0;               /* no state dependent codings */
  
          *s = wchar;
          return 1;
}
size_t mbstowcs(register wchar_t *pwcs, register const char *s, size_t n)
{
	  register int i = n;

	  while (--i >= 0) {
	          if (!(*pwcs++ = *s++))
	                  return n - i - 1;
	  }
	  return n - i;
}
size_t  wcstombs(register char *s, register const wchar_t *pwcs, size_t n)
{
	  register int i = n;

	  while (--i >= 0) {
	          if (!(*s++ = *pwcs++))
	                  break;
	  }
	  return n - i - 1;
}
