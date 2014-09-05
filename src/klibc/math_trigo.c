#include <math.h>

double acos(double x) 
{
        double pi;

        asm("fldpi" : "=t"(pi));

        return (pi / 2) - asin(x);
}

float acosf(float x) 
{
        float pi;
        asm("fldpi" : "=t"(pi));

        return (pi / 2) - asinf(x);
}

long double acosl(long double x) 
{
        long double pi;
        asm("fldpi" : "=t"(pi));

        return (pi / 2) - asinl(x);
}

double asin(double x) {
        return 2. * atan(x / (1. + sqrt(1. - x * x)));
}

float asinf(float x) {
        return 2. * atanf(x / (1. + sqrtf(1. - x * x)));
}

long double asinl(long double x) {
        return 2. * atanl(x / (1. + sqrtl(1. - x * x)));
}

double atan(double x) {
        return atan2(x, 1.);
}

float atanf(float x) {
        return atan2(x, 1.);
}

long double atanl(long double x) {
        return atan2(x, 1.);
}

double atan2(double y, double x) 
{
        double result;
        asm("fld %1 ; fld %2 ; fpatan" : "=t"(result) : "m"(y), "m"(x));
        return result;
}

float atan2f(float y, float x) 
{
        float result;
        asm("fld %1 ; fld %2 ; fpatan" : "=t"(result) : "m"(y), "m"(x));
        return result;
}

long double atan2l(long double y, long double x)
{
        long double result;
        asm("fld %1 ; fld %2 ; fpatan" : "=t"(result) : "m"(y), "m"(x));
        return result;
}

double cos(double x) 
{
        asm("fcos" : "+t"(x));
        return x;
}

float cosf(float x) 
{
        asm("fcos" : "+t"(x));
        return x;
}

long double cosl(long double x) 
{
        asm("fcos" : "+t"(x));
        return x;
}

double sin(double x) 
{
        asm("fsin" : "+t"(x));
        return x;
}

float sinf(float x) 
{
        asm("fsin" : "+t"(x));
        return x;
}

long double sinl(long double x) 
{
        asm("fsin" : "+t"(x));
        return x;
}

double tan(double x) 
{
        return sin(x) / cos(x);
}

float tanf(float x) 
{
        return sinf(x) / cosf(x);
}

long double tanl(long double x) 
{
        return sinl(x) / cosl(x);
}

double acosh(double x) 
{
        return log(x + sqrt(x * x - 1));
}

float acoshf(float x) 
{
        return logf(x + sqrtf(x * x - 1));
}

long double acoshl(long double x) 
{
        return logl(x + sqrtl(x * x - 1));
}

double asinh(double x) 
{
        return log(x + sqrt(x * x + 1));
}

float asinhf(float x) 
{
        return logf(x + sqrtf(x * x + 1));
}

long double asinhl(long double x) 
{
        return logl(x + sqrtl(x * x + 1));
}

double atanh(double x) 
{
        return 0.5 * log((1. + x) / (1. - x));
}

float atanhf(float x) 
{
        return 0.5 * logf((1. + x) / (1. - x));
}

long double atanhl(long double x) 
{
        return 0.5 * logl((1. + x) / (1. - x));
}

double cosh(double x) 
{
        return (exp(x) + exp(-x)) * 0.5;
}

float coshf(float x) 
{
        return (exp(x) + exp(-x)) * 0.5;
}

long double coshl(long double x) 
{
        return (exp(x) + exp(-x)) * 0.5;
}

double sinh(double x) 
{
        return (exp(x) - exp(-x)) * 0.5;
}

float sinhf(float x) 
{
        return (exp(x) - exp(-x)) * 0.5;
}

long double sinhl(long double x) 
{
        return (exp(x) - exp(-x)) * 0.5;
}

double tanh(double x) 
{
        return sinh(x) / cosh(x);
}

float tanhf(float x) 
{
        return sinhf(x) / coshf(x);
}

long double tanhl(long double x) 
{
        return sinhl(x) / coshl(x);
}
