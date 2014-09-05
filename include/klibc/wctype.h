#ifndef _WCTYPE_H
#define _WCTYPE_H

#include <wchar.h>
#include <types.h>

typedef const int32_t* wctrans_t;
#ifdef __cplusplus
extern "C" 
{
#endif

int iswalnum(wint_t); //
int iswalpha(wint_t); //
int iswblank(wint_t); //
int iswcntrl(wint_t); //
int iswdigit(wint_t); //
int iswgraph(wint_t); //
int iswlower(wint_t); //
int iswprint(wint_t); //
int iswpunct(wint_t); //
int iswspace(wint_t); //
int iswupper(wint_t); //
int iswxdigit(wint_t); //

wchar_t towlower(wchar_t); //
wchar_t towupper(wchar_t); //

int iswctype(wint_t , wctype_t); //
wctype_t wctype(const char *) ; //

wctrans_t wctrans(const char *); //
wint_t towctrans(wint_t , wctrans_t); //


#ifdef __cplusplus
};
#endif

#endif
