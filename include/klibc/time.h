
#ifndef KLIBC_TIME_H
#define KLIBC_TIME_H


#ifdef __cplusplus
extern "C"
{
#endif

typedef long int clock_t;
typedef long int time_t;

struct tm
{
        int tm_year, tm_mon, tm_mday, tm_hour, tm_min, tm_sec;
};

struct tm *localtime ( const time_t * timer);
char* asctime(const struct tm *timeptr);

#ifdef __cplusplus
};
#endif

#endif