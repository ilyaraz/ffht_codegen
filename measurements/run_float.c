#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "to_run.h"

int main(void) {
    srand(4057218);
    int n = 1 << log_n;
    void *buf = malloc(sizeof(float) * n + 32);
    char *start = buf;
    while ((size_t)start % 32 != 0) start = start + 1;
    float *a = (float*)start;
    for (int i = 0; i < n; ++i) {
        a[i] = 1.0 - 2.0 * (rand() % 2);
    }
    for (long long num_it = 10;; num_it *= 2) {
        clock_t tt1 = clock();
        float dummy = 0.0;
        for (long long it = 0; it < num_it; ++it) {
            run(a);
            dummy += a[0];
        }
        clock_t tt2 = clock();
        double sec = (tt2 - tt1) / (CLOCKS_PER_SEC + 0.0);
        if (sec >= 1.0) {
            double tm = sec / (num_it + 0.0);
            printf("%.10e\n", tm);
            fprintf(stderr, "dummy = %f\n", dummy);
            FILE *output = fopen("time.txt", "w");
            fprintf(output, "%.10e\n", tm);
            fclose(output);
            break;
        }
    }
    free(buf);
    return 0;
}
