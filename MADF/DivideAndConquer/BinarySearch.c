#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(char *arr[], int low, int high, char *x) {
    if (low == high) {
        printf(" %02d      %02d\n", low, high);
        if (strcmp(arr[low], x) == 0)
            return low;
        else
            return -1;
    } else {
        int mid = (low + high) / 2;
        printf(" %02d  %02d  %02d\n", low,mid, high);
        if (strcmp(arr[mid], x) == 0)
            return mid;

        else if (strcmp(arr[mid], x) > 0)
            return binarySearch(arr, low, mid - 1, x);
        else
            return binarySearch(arr, mid + 1, high, x);
    }

    return -1;
}

int main() {
    int n;
    printf("Enter number of strings: ");
    scanf("%d", &n);

    char **arr = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        arr[i] = (char *)malloc(100 * sizeof(char));
        printf("Enter string %d: ", i + 1);
        scanf("%s", arr[i]);
    }

    char x[100];
    printf("Enter string to search: ");
    scanf("%s", x);

    clock_t start, end;
    double cpu_time_used;

    printf("\nLow Mid High\n");
    start = clock();
    int result = binarySearch(arr, 0, n - 1, x);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (result != -1)
        printf("String found at index %d\n", result+1);
    else
        printf("String not found\n");

    printf("Time taken for binary search: %f seconds\n\n", cpu_time_used);

    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}