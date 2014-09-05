#ifndef KLIBC_WSTRING_H
#define KLIBC_WSTRING_H

#include <klibc/stddef.h>
#include <klibc/stdarg.h>
#include <klibc/stdio.h>

#if defined(__WINT_TYPE__)
typedef __WINT_TYPE__ wint_t;
#else
typedef unsigned int wint_t;
#endif
typedef int (*wctype_t)(wint_t);

#ifndef WCHAR_MIN
#define WCHAR_MIN (-2147483647 - 1)
#define WCHAR_MAX (2147483647)
#endif
#ifndef WEOF
#define WEOF 0xffffffffu
#endif

#ifdef __cplusplus
extern "C" 
{
#endif


wchar_t*   	wcsccpy  (wchar_t* s1, const wchar_t* s2);
wchar_t*   	wcscncpy (wchar_t* dst, const wchar_t* src, size_t n);
wchar_t*   	wcsccat  (wchar_t* s1, const wchar_t* s2);
wchar_t*	wcsncat(wchar_t *  s1, const wchar_t *  s2, size_t n);

int 		wcscmp(const wchar_t *s1, const wchar_t *s2);
int  		wcsncmp (const wchar_t* s1, const wchar_t* s2, size_t n);

wchar_t *	wcschr(const wchar_t *s, wchar_t c);
size_t 		wcsspn(const wchar_t *s, const wchar_t *set);
wchar_t *	wcspbrk(const wchar_t *s, const wchar_t *set);
wchar_t *	wcsrchr(const wchar_t *s, wchar_t c);
size_t  	wcscspn  (const wchar_t *s, const wchar_t *set);
wchar_t *	wcsstr(const wchar_t *  s, const wchar_t *  find);
wchar_t*   	wcstok(wchar_t *  s, const wchar_t *  delim,  wchar_t **  last);
size_t  	wcslen  (const wchar_t* s);
size_t 		wcsnlen(const wchar_t *s, size_t maxlen);
wchar_t *	wcsdup (const wchar_t *s);

size_t 		wcslcat(wchar_t *dst, const wchar_t *src, size_t siz);
size_t 		wcslcpy(wchar_t *dst, const wchar_t *src, size_t siz);

wchar_t	*	wmemchr(const wchar_t *s, wchar_t c, size_t n);
int 		wmemcmp(const wchar_t *s1, const wchar_t *s2, size_t n);
wchar_t *	wmemcpy(wchar_t *destination, const wchar_t *source, size_t num);
wchar_t *	wmemmove(wchar_t *destination, const wchar_t *source, size_t num);
wchar_t *	wmemset(wchar_t *s, wchar_t c, size_t n);


#ifdef __cplusplus
};
#endif

#endif