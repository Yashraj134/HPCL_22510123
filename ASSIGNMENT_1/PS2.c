#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads;

    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    
    printf("\nSequential Hello:\n");
    for (int i = 0; i < num_threads; i++) {
        printf("Hello from thread %d (Sequential)\n", i);
        
    }

    printf("\nParallel Hello:\n");
    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();  
        printf("Hello from thread %d (Parallel)\n", tid);
    }

    return 0;
}
