#include <cstdio>
#include <omp.h>

#define N 1000
#define CHUNKSIZE 100

int main(int argc, char *argv[]) {
    int nthreads, tid;
    /* Fork a team of threads with each thread having a private tid variable */
    #pragma omp parallel default(none) private(tid) shared(nthreads)
    {
        /* Obtain and print thread id */
        tid = omp_get_thread_num();
        printf("Hello OpenMP from thread = %d\n", tid);

        /* Only master thread does this */
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    } /* All threads join master thread and terminate */


    int i, chunk;
    float a[N], b[N], c[N];

    /* Some initializations */
    for (i = 0; i < N; i++)
        a[i] = b[i] = i * 1.0;
    chunk = CHUNKSIZE;

    #pragma omp parallel default(none) shared(a, b, c, chunk) private(i)
    {
        #pragma omp for schedule(dynamic, chunk) nowait
        for (i = 0; i < N; i++)
            c[i] = a[i] + b[i];
    } /* end of parallel region */

    float sum = 0.0;
    #pragma omp for schedule(dynamic) /* calculate sum of vector c */
    for (i = 0; i < N; i++)
        sum += c[i];

    printf("Sum = %f\n", sum);

    return 0;
}