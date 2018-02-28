/**
 * A program to calculate the minimum edit distance from string a to string b
 *
 * Uses the Bottom Up approach
 *
 * @see https://www.youtube.com/watch?v=b6AGUjqIPsA
 * Special thank you to Vivekanand for his YouTube video on this topic
 */

#include <stdio.h>
#include <stdint.h> // uint64_t
#include <stdlib.h>
#include <string.h>

#include "performance.c"

// function prototypes
uint64_t min_out_of_three(uint64_t a, uint64_t b, uint64_t c);
uint64_t str_min_distance(char *str1, char *str2);

// main
int main(int argc, char *argv[])
{
    // validate number of arguments
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s string string\n", argv[0]);
        return 1;
    }

    // alias strings
    char *str1 = argv[1];
    char *str2 = argv[2];

    // performance benchmark
    rusage before, after;
    double time_calc = 0.0;

    getrusage(RUSAGE_SELF, &before);
    uint64_t result = str_min_distance(str1, str2);
    getrusage(RUSAGE_SELF, &after);

    time_calc = calculate(&before, &after);

    printf("RESULT:                     %lu\n", result);
    printf("TIME IN str_min_distance(): %.2f\n", time_calc);

    return 0;
}

/**
 * Return the minimum of 3 integers
 */
uint64_t min_out_of_three(uint64_t a, uint64_t b, uint64_t c)
{
    if (a < b && a < c)
    {
        return a;
    }
    else if (b < a && b < c)
    {
        return b;
    }
    return c;
}

/**
 * Calculate the minimum distance between strings
 *
 * Example: "abc" to "ab"

    +------+-------------------
    |      | NULL   a   b   c
    +------+-------------------
    | NULL | 0      1   2   3
    | a    | 1      0   1   2
    | b    | 2      1   0   1
    +------+-------------------

 * @see http://truben.no/table/
 *
 * T(n) = T(str1_len) * T(str2_len) = T(n * m) = O(nm);
 */
uint64_t str_min_distance(char *str1, char *str2)
{
    size_t str1_len = strlen(str1);
    size_t str2_len = strlen(str2);

    // memo table
    uint64_t memo[str1_len + 1][str2_len + 1]; // + 1 to account for NULL

    // rows
    for (size_t row = 0; row <= str1_len; row++)
    {
        // columns
        for (size_t col = 0; col <= str2_len; col++)
        {
            // base case (0,0) i.e. NULL
            if (row == 0 && col == 0)
            {
                // how many steps does it take to get from NULL to NULL?
                // # operations
                memo[row][col] = 0;
            }
            // base case [1, str2_len]
            else if (row == 0)
            {
                // add 1 to the number of operations previously made (horizontal, str1)
                // # operations
                memo[row][col] = memo[row][col - 1] + 1;
            }
            // base case [1, str1_len]
            else if (col == 0)
            {
                // add 1 to the number of operations previously made (vertical, str2)
                // # operations
                memo[row][col] = memo[row - 1][col] + 1;
            }
            // inner matrix
            else
            {
                // char at col equals the char at row
                if (str1[col - 1] == str2[row - 1])
                {
                    // copy the diagonal element
                    memo[row][col] = memo[row - 1][col - 1];
                }
                // chars are different
                else
                {
                    // take the minimum of the replace, remove, insert operations
                    // add 1 since we are performing another operation
                    memo[row][col] = min_out_of_three(memo[row][col - 1], memo[row - 1][col], memo[row - 1][col - 1]) + 1;
                }
            }
        } // columns
    } // rows

    // return the bottom right cell that represents the minimum distance to change all characters
    return memo[str1_len][str2_len];
}
