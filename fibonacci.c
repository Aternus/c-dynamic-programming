/**
 * A program to calculate the n^th^ Fibonacci number
 *
 * Using Recursion
 */

#include <stdio.h>
#include <stdint.h> // uint64_t
#include <stdlib.h>

#include "performance.c"

// function prototypes
uint64_t fib(int n);

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
    // no greater than 93 so that the result is in the supported range of 64bit CPU
    if (n < 1 || n > 93)
    {
        fprintf(stderr, "0 < n <= 93\n");
        return 1;
    }

    // performance benchmark
    rusage before, after;
    double time_calc = 0.0;

    getrusage(RUSAGE_SELF, &before);
    uint64_t result = fib(n);
    getrusage(RUSAGE_SELF, &after);

    time_calc = calculate(&before, &after);

    printf("RESULT:      %lu\n", result);
    printf("TIME IN fib: %.2f\n", time_calc);

    return 0;
}

/**
 * Calculate the n^th^ Fibonacci number
 *
 * Fibonacci sequence: 1, 1, 2, 3, 5, 8, etc.
 *
 * T(n) = T(n-1) + T(n-2) + O(1) ≈ T(Φ^n) + O(1) ≈ O(2^n^)
 */
uint64_t fib(int n)
{
    uint64_t result = 0;
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
