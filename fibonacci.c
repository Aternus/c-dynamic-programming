/**
 * A program to calculate the n^th^ Fibonacci number
 *
 * Using Recursion
 *
 * T(n) = O(2^n^)
 */

#include <stdio.h>
#include <stdlib.h>

#include "performance.c"

// function prototypes
unsigned long long fib(int n);

// main
int main(int argc, char *argv[])
{
    // validate number of arguments
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s n\n", argv[0]);
        return 1;
    }

    // convert n to int
    int n = atoi(argv[1]);

    // validate that n is a positive integer
    if (n < 1)
    {
        fprintf(stderr, "n must be a positive integer value\n");
        return 1;
    }

    // performance benchmark
    rusage before, after;
    double time_calc = 0.0;

    getrusage(RUSAGE_SELF, &before);
    unsigned long long result = fib(n);
    getrusage(RUSAGE_SELF, &after);

    time_calc = calculate(&before, &after);

    printf("RESULT:      %llu\n", result);
    printf("TIME IN fib: %.2f\n", time_calc);

    return 0;
}

/**
 * Calculate the n^th^ Fibonacci number
 *
 * Fibonacci sequence: 1, 1, 2, 3, 5, 8, etc.
 */
unsigned long long fib(int n)
{
    int result = 0;
    // base case
    if (n == 1 || n == 2)
    {
        result = 1;
    }
    // recursion case
    else
    {
        result = fib(n - 1) + fib(n - 2);
    }
    return result;
}
