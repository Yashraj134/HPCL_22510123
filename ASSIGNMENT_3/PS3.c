#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 200

int main() {
    int vector[SIZE];
    int scalar = 5;
    double start, end;
    int chunk_sizes[] = {1, 5, 10, 20, 50, 100};


    for (int i = 0; i < SIZE; i++)
        vector[i] = i;

    printf("STATIC SCHEDULE:\n");
    for (int c = 0; c < 6; c++) {
        int chunk = chunk_sizes[c];
        start = omp_get_wtime();

        #pragma omp parallel for schedule(static, chunk)
        for (int i = 0; i < SIZE; i++) {
            vector[i] += scalar;
        }

        end = omp_get_wtime();
        printf("Chunk size: %3d | Time: %f seconds\n", chunk, end - start);
    }

    printf("\nDYNAMIC SCHEDULE:\n");
    for (int c = 0; c < 6; c++) {
        int chunk = chunk_sizes[c];
        start = omp_get_wtime();

        #pragma omp parallel for schedule(dynamic, chunk)
        for (int i = 0; i < SIZE; i++) {
            vector[i] += scalar;
        }

        end = omp_get_wtime();
        printf("Chunk size: %3d | Time: %f seconds\n", chunk, end - start);
    }

    printf("\nNOWAIT DEMONSTRATION:\n");

    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < SIZE / 2; i++) {
            vector[i] += scalar;
        }

        #pragma omp for
        for (int i = SIZE / 2; i < SIZE; i++) {
            vector[i] += scalar;
        }
    }

    printf("Nowait used without barrier after first loop.\n");

    return 0;
}
