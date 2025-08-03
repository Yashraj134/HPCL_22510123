#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int arr[], int left, int mid, int right, int ascending) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (ascending) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
        } else {
            if (L[i] >= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right, int ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSort(arr, left, mid, ascending);
            }
            #pragma omp section
            {
                mergeSort(arr, mid + 1, right, ascending);
            }
        }
        
        merge(arr, left, mid, right, ascending);
    }
}
int main() {
    int n, num_threads;
    
    printf("Enter the size of vectors: ");
    scanf("%d", &n);
    
    printf("Enter number of threads: ");
    scanf("%d", &num_threads);
    
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));

    printf("Enter elements of first vector:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    printf("Enter elements of second vector:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }
    
    double start_time = omp_get_wtime();
    
    mergeSort(a, 0, n-1, 1);
    mergeSort(b, 0, n-1, 0);
    
    long long dot_product = 0;
    
    #pragma omp parallel for reduction(+:dot_product) num_threads(num_threads)
    for(int i = 0; i < n; i++) {
        dot_product += (long long)a[i] * b[i];
    }
    
    double end_time = omp_get_wtime();
    
    printf("\n\nMinimum scalar product: %lld\n", dot_product);
    printf("Time taken with %d threads: %f seconds\n", num_threads, end_time - start_time);
    
    free(a);
    free(b);
    
    return 0;
}