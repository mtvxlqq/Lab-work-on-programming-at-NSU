#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int start, int end) {
    int root = start;

    while (root * 2 + 1 <= end) {
        int child = root * 2 + 1;
        int swap_idx = root;

        if (arr[swap_idx] < arr[child]) {
            swap_idx = child;
        }
        if (child + 1 <= end && arr[swap_idx] < arr[child + 1]) {
            swap_idx = child + 1;
        }

        if (swap_idx == root) {
            return;
        } else {
            swap(&arr[root], &arr[swap_idx]);
            root = swap_idx;
        }
    }
}

void heap_sort(int arr[], int N) {
    for (int i = N / 2 - 1; i >= 0; i--) {
        heapify(arr, i, N - 1);
    }

    for (int i = N - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        
        heapify(arr, 0, i - 1);
    }
}

int main(void) {
    int N;

    if (scanf("%d", &N) != 1) {
        printf("bad input\n");
        return 0;
    }

    int *arr = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("bad input\n");
            free(arr);
            return 0;
        }
    }
    
    heap_sort(arr, N); 

    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    free(arr);
    
    return 0;
}