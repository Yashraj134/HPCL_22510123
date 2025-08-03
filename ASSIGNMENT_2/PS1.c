#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n, i, th;
    float scalar;

    printf("Enter the size of the vector: ");
    scanf("%d", &n);
    
    printf("Enter the scalar value to add: ");
    scanf("%f", &scalar);

    float *vec = (float *)malloc(n * sizeof(float));

    for (i = 0; i < n; i++) {
        vec[i] = i * 1.0f;
    }

    double start_time = omp_get_wtime();

    printf("Enter number of threads : ");
    scanf("%d", &th);

    omp_set_num_threads(th);
    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        vec[i] = vec[i] + scalar;
    }

    double end_time = omp_get_wtime();

    printf("First 5 results after scalar addition :\n");
    for (i = 0; i < 5 && i < n; i++) {
        printf("vec[%d] = %.2f\n", i, vec[i]);
    }

    printf("Time taken: %.6f seconds\n", end_time - start_time);

    free(vec);
    return 0;
}
