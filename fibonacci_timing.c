#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

/*
 * The assignment didn't specify what language to use, so I did it in c for fun.
 * I also did it with dynamic, procedural, and recurdive appraches and calculated the time they took
 */


uintmax_t fib_dynamic(int n)
{
    uintmax_t final;

    if (n == 0 || n == 1)
    {
        return n;
    }

    uintmax_t *nums = malloc((n + 1) * sizeof(uintmax_t));

    nums[0] = 0;
    nums[1] = 1;

    for (int i = 2; i < n; i++)
    {
        nums[i] = nums[i - 1] + nums[i - 2];
    }

    final = nums[n];
    free(nums);

    return final;
}

uintmax_t fib_procedural(int n)
{

    uintmax_t a = 0;
    uintmax_t b = 1;
    uintmax_t c = 0;

    // procedural
    for (int i = 0; i < n; i++)
    {
        c = a + b;
        b = a;
        a = c;
    }

    return a;
}

uintmax_t fib_recursive(int n)
{
    if (n == 0 || n == 1)
    {
        return n;
    }

    return fib_recursive(n - 1) + fib_recursive(n - 2);
}


struct timespec test_fib_calc_time(uintmax_t (*function)(int), int index)
{
    struct timespec start, end;
    struct timespec execution_time;

    clock_gettime(CLOCK_MONOTONIC, &start);
    uintmax_t result = (*function)(index);
    clock_gettime(CLOCK_MONOTONIC, &end);

    execution_time.tv_sec = end.tv_sec - start.tv_sec;
    execution_time.tv_nsec = end.tv_nsec - start.tv_nsec;
    return execution_time;
}


// long long time_to_percentage(time_t time, time_t lowest_time, time_t highest_time) {

//     int final_size = 100;
//     time_t time_difference = highest_time - lowest_time;



//     long long outgoing = (final_size / time_difference) * (time - lowest_time);
//     return outgoing;
// }



int main(int charc, char *argv[])
{

    int index;
    printf("what index do you want? ");
    scanf("%d", &index);

    printf("Fibonacci Number of index %d:\n    %lu\n\n", index, fib_procedural(index));

    // say how long things took
    struct timespec dynamic_time, recursive_time, procedural_time;

    dynamic_time = test_fib_calc_time(&fib_dynamic, index);
    procedural_time = test_fib_calc_time(&fib_procedural, index);
    recursive_time = test_fib_calc_time(&fib_recursive, index);

    printf("Time for dynamic programming: %ld seconds and %ld nanoseconds\n", dynamic_time.tv_sec, dynamic_time.tv_nsec);
    printf("Time for procedural programming: %ld seconds and %ld nanoseconds\n", procedural_time.tv_sec, procedural_time.tv_nsec);
    printf("Time for functional(recursive) programming: %ld seconds and %ld nanoseconds\n", recursive_time.tv_sec, recursive_time.tv_nsec);

    /*
    * I think it would be cool to add a little bar graph thing to compare their times
    something like this
    R  P  D
    #
    #     #
    #  #  #
    #  #  #
    */

    return 0;
}
