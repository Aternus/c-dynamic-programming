/**
 * A program to calculate the n^th^ Fibonacci number
 *
 * Using Recursion + Store (Memoize)
 *
 * T(n) = number of calls to fib() * time = 2n + 1 * 1 = O(2n+1) ≈ O(n)
 */

#include <stdio.h>
#include <stdlib.h>

#include "performance.c"

// function prototypes
unsigned long long fib(int n, unsigned long long *memo);

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

    // allocate memory for the memoized array
    unsigned long long *memo = calloc(n + 1, sizeof(unsigned long long));

    getrusage(RUSAGE_SELF, &before);
    unsigned long long result = fib(n, memo);
    getrusage(RUSAGE_SELF, &after);

    // free memory allocated for the memoized array
    free(memo);

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
unsigned long long fib(int n, unsigned long long *memo)
{
    int result = 0;
    // base cases
    if (memo[n] != 0)
    {
        return memo[n];
    }
    else if (n == 1 || n == 2)
    {
        result = 1;
    }
    // recursion case
    else
    {
        result = fib(n - 1, memo) + fib(n - 2, memo);
    }
    memo[n] = result;
    return result;
}
