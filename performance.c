/**
 * Performance measurement drop-in
 */

#include <sys/resource.h>
#include <sys/time.h>

// import "struct rusage" as "rusage"
typedef struct rusage rusage;

/**
 * Returns number of seconds between b and a
 */
double calculate(rusage *b, rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((
                    ((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) - (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                    ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) - (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec))
                ) / 1000000.0);
    }
}
