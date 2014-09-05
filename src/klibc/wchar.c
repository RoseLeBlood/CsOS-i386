#include <wchar.h>
#include <string.h>
#include <malloc.h>

wchar_t*   	wcsccpy  (wchar_t* s1, const wchar_t* s2)
{
	wchar_t *cp;

	cp = s1;
	while ((*cp++ = *s2++) != L'\0')
		;

	return (s1);
}
wchar_t*   	wcscncpy (wchar_t* dst, const wchar_t* src, size_t n)
{
	for (; n--; dst++, src++) 
	{
		if (!(*dst = *src)) 
		{
			wchar_t *ret = dst;
			while (n--)
				*++dst = L'\0';
			return (ret);
		}
	}
	return (dst);
}
wchar_t*   	wcsccat  (wchar_t* s1, const wchar_t* s2)
{
	wchar_t *cp;

	cp = s1;
	while (*cp != L'\0')
		cp++;
	while ((*cp++ = *s2++) != L'\0');

	return (s1);
}
wchar_t *wcsncat(wchar_t *  s1, const wchar_t *  s2, size_t n)
{
	wchar_t *p;
	wchar_t *q;
	const wchar_t *r;

	p = s1;
	while (*p)
		p++;
	q = p;
	r = s2;
	while (*r && n) 
	{
		*q++ = *r++;
		n--;
	}
	*q = '\0';
	return s1;
}

int wcscmp(const wchar_t *s1, const wchar_t *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == '\0')
			return (0);
	return (*(const unsigned int *)s1 - *(const unsigned int *)--s2);
}
int  wcsncmp (const wchar_t* s1, const wchar_t* s2, size_t n) 
{
	if (n == 0)
		return (0);
	do 
	{
		if (*s1 != *s2++) 
		{
			return (*(const unsigned int *)s1 -
			    *(const unsigned int *)--s2);
		}
		if (*s1++ == 0)
			break;
	} while (--n != 0);
	return (0);
}

wchar_t *wcschr(const wchar_t *s, wchar_t c)
{

	while (*s != c && *s != L'\0')
		s++;
	if (*s == c)
		return ((wchar_t *)s);
	return (NULL);
}
size_t wcsspn(const wchar_t *s, const wchar_t *set)
{
	const wchar_t *p;
	const wchar_t *q;

	p = s;
	while (*p) 
	{
		q = set;
		while (*q) 
		{
			if (*p == *q)
				break;
			q++;
		}
		if (!*q)
			goto done;
		p++;
	}

done:
	return (p - s);
}
wchar_t *wcspbrk(const wchar_t *s, const wchar_t *set)
{
	const wchar_t *p;
	const wchar_t *q;

	p = s;
	while (*p) 
	{
		q = set;
		while (*q) 
		{
			if (*p == *q) 
			{
				return (wchar_t *)p;
			}
			q++;
		}
		p++;
	}
	return NULL;
}
wchar_t *wcsrchr(const wchar_t *s, wchar_t c)
{
	const wchar_t *last;

	last = NULL;
	for (;;) 
	{
		if (*s == c)
			last = s;
		if (*s == L'\0')
			break;
		s++;
	}

	return ((wchar_t *)last);
}
size_t  	wcscspn  (const wchar_t *s, const wchar_t *set)
{
	const wchar_t *p;
	const wchar_t *q;

	p = s;
	while (*p) 
	{
		q = set;
		while (*q) 
		{
			if (*p == *q)
				goto done;
			q++;
		}
		p++;
	}

done:
	return (p - s);
}
wchar_t *wcsstr(const wchar_t *  s, const wchar_t *  find)
{
	wchar_t c, sc;
	size_t len;

	if ((c = *find++) != L'\0') 
	{
		len = wcslen(find);
		do 
		{
			do 
			{
				if ((sc = *s++) == L'\0')
					return (NULL);
			} while (sc != c);
		} while (wcsncmp(s, find, len) != 0);
		s--;
	}
	return ((wchar_t *)s);
}
wchar_t*   	wcstok(wchar_t *  s, const wchar_t *  delim,  wchar_t **  last)
{
	const wchar_t *spanp;
	wchar_t *tok;
	wchar_t c, sc;

	if (s == NULL && (s = *last) == NULL)
		return (NULL);

cont:
	c = *s++;
	for (spanp = delim; (sc = *spanp++) != L'\0';) 
	{
		if (c == sc)
			goto cont;
	}

	if (c == L'\0') 
	{	
		*last = NULL;
		return (NULL);
	}
	tok = s - 1;

	for (;;) 
	{
		c = *s++;
		spanp = delim;
		do {
			if ((sc = *spanp++) == c) 
			{
				if (c == L'\0')
					s = NULL;
				else
					s[-1] = L'\0';
				*last = s;
				return (tok);
			}
		} while (sc != L'\0');
	}
}
size_t  	wcslen  (const wchar_t* s)  
{
	const wchar_t *p;

	p = s;
	while (*p)
		p++;

	return p - s;
}
size_t wcsnlen(const wchar_t *s, size_t maxlen)
{
	size_t len;

	for (len = 0; len < maxlen; len++, s++) 
	{
		if (!*s)
			break;
	}
	return (len);
}
wchar_t *	wcsdup (const wchar_t *s)
{
	wchar_t *copy;
	size_t len;

	len = wcslen(s) + 1;
	if ((copy = (wchar_t*)malloc(len * sizeof(wchar_t))) == NULL)
		return (NULL);
	return (wmemcpy(copy, s, len));
}
long 		wcsctol(const wchar_t *str, wchar_t **endptr, int base);

size_t wcslcat(wchar_t *dst, const wchar_t *src, size_t siz)
{
	wchar_t *d = dst;
	const wchar_t *s = src;
	size_t n = siz;
	size_t dlen;

	while (*d != '\0' && n-- != 0)
		d++;
	dlen = d - dst;
	n = siz - dlen;

	if (n == 0)
		return(dlen + wcslen(s));
	while (*s != '\0') 
	{
		if (n != 1) 
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';

	return(dlen + (s - src));	/* count does not include NUL */
}
size_t wcslcpy(wchar_t *dst, const wchar_t *src, size_t siz)
{
	wchar_t *d = dst;
	const wchar_t *s = src;
	size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0 && --n != 0) 
	{
		do 
		{
			if ((*d++ = *s++) == 0)
				break;
		} while (--n != 0);
	}

	if (n == 0) 
	{
		if (siz != 0)
			*d = '\0';	
		while (*s++) ;
	}

	return(s - src - 1);	
}
wchar_t	*wmemchr(const wchar_t *s, wchar_t c, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++) 
	{
		if (*s == c) 
		{
			return (wchar_t *)s;
		}
		s++;
	}
	return NULL;
}
int 		wmemcmp(const wchar_t *s1, const wchar_t *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++) 
	{
		if (*s1 != *s2) 
		{
			return *s1 > *s2 ? 1 : -1; 
		}
		s1++;
		s2++;
	}
	return 0;
}
wchar_t *	wmemcpy(wchar_t *destination, const wchar_t *source, size_t num)
{
	return (wchar_t *)memcpy(destination, source, num * sizeof(wchar_t));
}
wchar_t *	wmemmove(wchar_t *destination, const wchar_t *source, size_t num)
{
	return (wchar_t *)memmove(destination, source, num * sizeof(wchar_t));
}
wchar_t *	wmemset(wchar_t *s, wchar_t c, size_t n)
{	
	size_t i;
	wchar_t *p;

	p = (wchar_t *)s;
	for (i = 0; i < n; i++) 
	{
		*p = c;
		p++;
	}
	return s;
}


