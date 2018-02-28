/**
 * A program to calculate the n^th^ Fibonacci number
 *
 * Using Recursion and Memoization
 */

#include <stdio.h>
#include <stdint.h> // uint64_t
#include <stdlib.h>

#include "performance.c"

// function prototypes
uint64_t fib(int n, uint64_t *memo);

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

    // allocate memory for the memo array
    uint64_t *memo = calloc(n + 1, sizeof(uint64_t));

    getrusage(RUSAGE_SELF, &before);
    uint64_t result = fib(n, memo);
    getrusage(RUSAGE_SELF, &after);

    // free memory allocated for the memo array
    free(memo);

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
 * T(n) = #subproblems * time/subproblem * O(1)
 *
 *        #calls to fib() * time * O(1) = (2 * n + 1) * 1 * O(1) = O(2n+1) ≈ O(n)
 */
uint64_t fib(int n, uint64_t *memo)
{
    uint64_t result = 0;
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
