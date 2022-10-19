#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

const int N = 1e8;

int main() {
    int hits = 0;
    int i;
#pragma omp parallel for private(i) reduction(+:hits)
    for (i = 0; i < N; ++i) {
        unsigned int seed = (unsigned) 75432 * omp_get_thread_num() + i;
        double x = ((double)rand_r(&seed)) / RAND_MAX;
        double y = ((double)rand_r(&seed)) / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            hits += 1;
        }
    }
    printf("Hits: %d \n", hits);
    printf("N: %d \n", N);
    printf("Calculated pi number is: %f \n", 4 * (1.0 * hits) / (1.0 * N));
    return 0;
}