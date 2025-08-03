#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int **allocate_matrix(int size) {
    int **mat = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
        mat[i] = (int *)malloc(size * sizeof(int));
    return mat;
}

void fill_matrix(int **mat, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            mat[i][j] = rand() % 100;
}

void add_matrices(int **A, int **B, int **C, int size, int threads) {
    omp_set_num_threads(threads);
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int threads[] = {1, 2, 4, 8};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int num_threads = sizeof(threads) / sizeof(threads[0]);

    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        printf("\nMatrix size: %dx%d\n", size, size);

        int **A = allocate_matrix(size);
        int **B = allocate_matrix(size);
        int **C = allocate_matrix(size);

        fill_matrix(A, size);
        fill_matrix(B, size);

        double baseline_time = 0;

        for (int t = 0; t < num_threads; t++) {
            double start = omp_get_wtime();
            add_matrices(A, B, C, size, threads[t]);
            double end = omp_get_wtime();
            double time_taken = end - start;

            if (threads[t] == 1)
                baseline_time = time_taken;

            double speedup = baseline_time / time_taken;

            printf("threads: %d | time: %.6f sec | speedup: %.2f\n",
                   threads[t], time_taken, speedup);
        }

        for (int i = 0; i < size; i++) {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }
        free(A); free(B); free(C);
    }

    return 0;
}
