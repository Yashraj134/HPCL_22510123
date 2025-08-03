#include <stdio.h>
#include <omp.h>

int main() {
    long long num_steps;
    int num_threads;

    printf("Enter number of steps: ");
    
    scanf("%lld", &num_steps);

    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    double step = 1.0 / (double)num_steps;
    double sum = 0.0;

    double start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum) num_threads(num_threads)
    for (long long i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    double pi = step * sum;
    double end_time = omp_get_wtime();
    printf("\nEstimated Pi = %.10f\n", pi);
    printf("Time taken with %d threads = %f seconds\n", num_threads, end_time - start_time);
    return 0;
}
