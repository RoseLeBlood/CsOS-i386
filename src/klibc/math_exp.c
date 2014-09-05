
#include <math.h>

double exp(double x) 
{
        asm("fldl2e ; fmulp ; f2xm1" : "+t"(x));
        return x + 1;
}

float expf(float x) 
{
        asm("fldl2e ; fmulp ; f2xm1" : "+t"(x));
        return x + 1;
}

long double expl(long double x) 
{
        asm("fldl2e ; fmulp ; f2xm1" : "+t"(x));
        return x + 1;
}

double exp2(double x)
{
        asm("f2xm1" : "+t"(x));
        return x + 1;
}

float exp2f(float x) 
{
        asm("f2xm1" : "+t"(x));
        return x + 1;
}

long double exp2l(long double x) 
{
        asm("f2xm1" : "+t"(x));
        return x + 1;
}

double expm1(double x) {
        return exp(x) - 1;
}

float expm1f(float x) {
        return expf(x) - 1;
}

long double expm1l(long double x) 
{
        return expl(x) - 1;
}

double                  frexp(double x, int* exp);
float                           frexpf(float x, int* exp);
long double             frexpl(long double x, int* exp);
int                             ilogb(double x);
int                             ilogbf(float x);
int                             ilogbl(long double x);

double ldexp(double x, int exp) 
{
        return x * (1 << exp);
}

float ldexpf(float x, int exp) 
{
        return x * (1 << exp);
}

long double ldexpl(long double x, int exp) 
{
        return x * (1 << exp);
}

double log(double x) 
{
        double ln2;
        asm("fldln2" : "=t"(ln2));

        return ln2 * log2(x);
}

float logf(float x) 
{
        float ln2;

        asm("fldln2" : "=t"(ln2));

        return ln2 * log2f(x);
}

long double logl(long double x) 
{
        long double ln2;
        asm("fldln2" : "=t"(ln2));

        return ln2 * log2l(x);
}

double log10(double x) 
{
        double log10_2;
        asm("fldlg2" : "=t"(log10_2));

        return log10_2 * log2(x);
}

float log10f(float x) 
{
        double log10_2;
        asm("fldlg2" : "=t"(log10_2));

        return log10_2 * log2f(x);
}

long double log10l(long double x) 
{
        double log10_2;
        asm("fldlg2" : "=t"(log10_2));

        return log10_2 * log2l(x);
}

double log1p(double x) 
{
        return log(1 + x);
}

float log1pf(float x) 
{
        return logf(1 + x);
}

long double log1pl(long double x) 
{
        return logl(1 + x);
}

double log2(double x) 
{
        asm("fld1 ; fxch ; fyl2x" : "+t"(x));
        return x;
}

float log2f(float x) 
{
        asm("fld1 ; fxch ; fyl2x" : "+t"(x));
        return x;
}

long double log2l(long double x)
{
        asm("fld1 ; fxch ; fyl2x" : "+t"(x));
        return x;
}

double                  logb(double x);
float                           logbf(float x);
long double             logbl(long double x);
double                  modf(double value, double* iptr);
float                           modff(float value, float* iptr);
long double             modfl(long double value, long double* iptr);
double                  scalbn(double x, int n);
float                           scalbnf(float x, int n);
long double             scalbnl(long double x, int n);
double                  scalbln(double x, long int n);
float                           scalblnf(float x, long int n);
long double             scalblnl(long double x, long int n);
