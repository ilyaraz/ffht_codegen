#include <immintrin.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "routine.h"

int main(void) {
    int log_n;
    scanf("%d", &log_n);
    int n = 1 << log_n;
    void *buf = malloc(sizeof(float) * n + 32);
    void *start = buf;
    while ((size_t)start % 32) ++start;
    float *a = (float*)start;
    for (int num_it = 10;; num_it *= 2) {
        clock_t tt1 = clock();
        for (int it = 0; it < num_it; ++it) {
            fht(a, log_n);
        }
        clock_t tt2 = clock();
        double sec = (tt2 - tt1) / (CLOCKS_PER_SEC + 0.0);
        if (sec >= 1.0) {
            printf("%.10e\n", sec / (num_it + 0.0));
            break;
        }
    }
    return 0;
}
