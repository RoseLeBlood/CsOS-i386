
#ifndef KLIBC_STDIO_H
#define KLIBC_STDIO_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdarg.h>

#define 	EOF   (-1)

char 			*itoa				(int);
char 			*_itoa(char* result, int base, int value);
int 			atoi				(const char *);
int 			printf				(const char *, ...);
int 			scanf				(const char *, ...);
int 			getchar				();
int 			getch				();
char 			*gets				(char *);
char 			*itox				(int);
void 			cls();

int             snprintf            (char* s, size_t n, const char* format, ...);
int             sprintf         	(char* s, const char* format, ...);
int             sscanf          	(const char* s, const char* format, ...);
int             vsnprintf           (char* s, size_t n, const char* format, va_list arg);
int             vsprintf            (char* s, const char* format, va_list arg);
int             vsscanf         	(const char* s, const char* format, va_list arg);

char** 			make_args(char *str, unsigned int* size);
#ifdef __cplusplus
};
#endif

#endif