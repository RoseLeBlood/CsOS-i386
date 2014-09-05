#include <math.h>
#include <stdint.h>

double                  erf(double x);
float                           erff(float x);
long double             erfl(long double x);
double                  erfc(double x);
float                           erfcf(float x);
long double             erfcl(long double x);
double                  lgamma(double x);
float                           lgammaf(float x);
long double             lgammal(long double x);
double                  tgamma(double x);
float                           tgammaf(float x);
long double             tgammal(long double x);

double ceil(double x)
{
        // first we have to modify the CR field in the x87 control register
        uint_least16_t controlWord;
        asm volatile("fstcw %0" : : "m"(controlWord) : "memory");
        controlWord |= 0x400; controlWord &= ~0x800;
        asm volatile("fldcw %0" : : "m"(controlWord));
        return nearbyintl(x);
}

float ceilf(float x) 
{
        // first we have to modify the CR field in the x87 control register
        uint_least16_t controlWord;
        asm volatile("fstcw %0" : : "m"(controlWord) : "memory");
        controlWord |= 0x400; controlWord &= ~0x800;
        asm volatile("fldcw %0" : : "m"(controlWord));
        return nearbyintl(x);
}

long double ceill(long double x) 
{
        // first we have to modify the CR field in the x87 control register
        uint_least16_t controlWord;
        asm volatile("fstcw %0" : : "m"(controlWord) : "memory");
        controlWord |= 0x400; controlWord &= ~0x800;
        asm volatile("fldcw %0" : : "m"(controlWord));
        return nearbyintl(x);
}

double floor(double x) 
{
        // first we have to modify the CR field in the x87 control register
        uint_least16_t controlWord;
        asm volatile("fstcw %0" : : "m"(controlWord) : "memory");
        controlWord |= 0x800; controlWord &= ~0x400;
        asm volatile("fldcw %0" : : "m"(controlWord));
        return nearbyint(x);
}

float floorf(float x) 
{
        // first we have to modify the CR field in the x87 control register
        uint_least16_t controlWord;
        asm volatile("fstcw %0" : : "m"(controlWord) : "memory");
        controlWord |= 0x800; controlWord &= ~0x400;
        asm volatile("fldcw %0" : : "m"(controlWord));
        return nearbyintf(x);
}

long double floorl(long double x) 
{
        // first we have to modify the CR field in the x87 control register
        uint_least16_t controlWord;
        asm volatile("fstcw %0" : : "m"(controlWord) : "memory");
        controlWord |= 0x800; controlWord &= ~0x400;
        asm volatile("fldcw %0" : : "m"(controlWord));
        return nearbyintl(x);
}

double nearbyint(double x) 
{
        asm("frndint" : "+t"(x));
        return x;
}

float nearbyintf(float x)
{
        asm("frndint" : "+t"(x));
        return x;
}

long double nearbyintl(long double x) 
{
        asm("frndint" : "+t"(x));
        return x;
}

double                  rint(double x);
float                           rintf(float x);
long double             rintl(long double x);
long int                        lrint(double x);
long int                        lrintf(float x);
long int                        lrintl(long double x);
long long int           llrint(double x);
long long int           llrintf(float x);
long long int           llrintl(long double x);
double                  round(double x);
float                           roundf(float x);
long double             roundl(long double x);
long int                        lround(double x);
long int                        lroundf(float x);
long int                        lroundl(long double x);
long long int           llround(double x);
long long int           llroundf(float x);
long long int           llroundl(long double x);
double                  trunc(double x);
float                           truncf(float x);
long double             truncl(long double x);
double                  fmod(double x, double y);
float                           fmodf(float x, float y);
long double             fmodl(long double x, long double y);

double remainer(double x, double y) 
{
        double result;
        asm("fld %2 ; fld %1 ; fprem ; fxch ; fincstp" : "=t"(result) : "m"(x), "m"(y));

        return result;
}

float remainerf(float x, float y) 
{
        float result;

        asm("fld %2 ; fld %1 ; fprem ; fxch ; fincstp" : "=t"(result) : "m"(x), "m"(y));

        return result;
}

long double remainerl(long double x, long double y) 
{
        long double result;
        asm("fld %2 ; fld %1 ; fprem ; fxch ; fincstp" : "=t"(result) : "m"(x), "m"(y));

        return result;
}

double remquo(double x, double y, int* quo) {
        *quo = (int)x / (int)y;
        return remainer(x, y);
}

float remquof(float x, float y, int* quo) {
        *quo = (int)x / (int)y;
        return remainerf(x, y);
}

long double remquol(long double x, long double y, int* quo) {
        *quo = (int)x / (int)y;
        return remainerl(x, y);
}

double copysign(double x, double y) {
        double magnitude = fabs(x);
        return signbit(y) ? -magnitude : magnitude;
}

float copysignf(float x, float y) {
        double magnitude = fabsf(x);
        return signbit(y) ? -magnitude : magnitude;
}

long double copysignl(long double x, long double y) {
        double magnitude = fabsl(x);
        return signbit(y) ? -magnitude : magnitude;
}

double                  nan(const char* tagp);
float                           nanf(const char* tagp);
long double             nanl(const char* tagp);
double                  nextafter(double x, double y);
float                           nextafterf(float x, float y);
long double             nextafterl(long double x, long double y);
double                  nexttoward(double x, long double y);
float                           nexttowardf(float x, long double y);
long double             nexttowardl(long double x, long double y);

double fdim(double x, double y) {
        return (x > y) ? (x - y) : 0;
}

float fdimf(float x, float y) {
        return (x > y) ? (x - y) : 0;
}

long double fdiml(long double x, long double y) {
        return (x > y) ? (x - y) : 0;
}

double fmax(double x, double y) {
        return (x > y) ? x : y;
}

float fmaxf(float x, float y) {
        return (x > y) ? x : y;
}

long double fmaxl(long double x, long double y) {
        return (x > y) ? x : y;
}

double fmin(double x, double y) {
        return (x < y) ? x : y;
}

float fminf(float x, float y) {
        return (x < y) ? x : y;
}

long double fminl(long double x, long double y) {
        return (x < y) ? x : y;
}

double fma(double x, double y, double z) {
        return x * y + z;
}

float fmaf(float x, float y, float z) {
        return x * y + z;
}

long double fmal(long double x, long double y, long double z) {
        return x * y + z;
}
