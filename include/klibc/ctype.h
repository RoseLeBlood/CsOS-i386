
#ifndef KLIBC_CTYPE_H
#define KLIBC_CTYPE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <types.h>


int             isalnum (int c);
int             isalpha (int c);
int             isblank (int c);
int             iscntrl (int c);
int             isdigit (int c);
int             isgraph (int c);
int             islower (int c);
int             isprint (int c);
int             ispunct (int c);
int             isspace (int c);
int             isupper (int c);
int             isxdigit        (int c);
int             tolower (int c);
int             toupper (int c);
        
// macros for optimization
#define isalnum(c)                      (isalpha(c) || isdigit(c))
#define isalpha(c)                      (islower(c) || isupper(c))
#define isblank(c)                      ((c) == ' ' || (c) == '\t')
#define iscntrl(c)                      ((c) >= 0x0 && (c) <= 0x8)
#define isdigit(c)                      ((c) >= '0' && (c) <= '9')
#define isgraph(c)                      (ispunct(c) || isalnum(c))
#define islower(c)                      ((c) >= 'a' && (c) <= 'z')
#define isprint(c)                      (isgraph(c) || isspace(c))
#define ispunct(c)                      (((c) >= 0x21 && (c) <= 0x2F) || ((c) >= 0x3A && (c) <= 0x40) || ((c) >= 0x5B && (c) <= 0x60) || ((c) >= 0x7B && (c) <= 0x7E))
#define isspace(c)                      ((c) == ' ' || (c) == '\t' || (c) == '\r' || (c) == '\n' || (c) == '\f' || (c) == '\v')
#define isupper(c)                      ((c) >= 'A' && (c) <= 'Z')
#define isxdigit(c)                     (isdigit(c) || ((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F'))
#define tolower(c)                      (isupper(c) ? ((c) + 'a' - 'A') : (c))
#define toupper(c)                      (islower(c) ? ((c) + 'A' - 'a') : (c))



#ifdef __cplusplus
};
#endif

#endif