#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

void interchange(char arr[], int i, int j) {
    char temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(char arr[], int low, int high) {
    char pivot = arr[low];
    int i = low;
    int j = high;
    do {
        do {
            i++;
        } while(arr[i] <= pivot);
        do {
            j--;
        } while(arr[j] > pivot);

        printf("\n%3d  %3d", i + 1, j + 1);

        if (i < j) {
            interchange(arr, i, j);
        }
    } while(i < j);
    interchange(arr, low, j);
    printf("\n%3d  %3d", i + 1, j + 1);
    
    return j;
}

char KthSmallest(char arr[], int n, int k) {
    int low = 0, high = n - 1;
    // Set sentinel at arr[n]. Using CHAR_MAX as maximum
    arr[n+1] = CHAR_MAX;
    do {
        int j = partition(arr, low, high + 1);
        if(j == k - 1) {
            return arr[j];
        } else if(j > k - 1) {
            high = j - 1;
        } else {
            low = j + 1;
        }
    } while(1);
}

int main(){
    int n, k, choice;
    char arr[102]; // extra space for sentinel values
    double cpu_time_used;
    clock_t start, end;

    do {
        printf("\nMenu:\n");
        printf("1. Input Array\n");
        printf("2. Find Kth Smallest Element\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of characters in the array: ");
                scanf("%d", &n);
                printf("Enter the characters (separated by space):\n");
                for (int i = 0; i < n; i++) {
                    scanf(" %c", &arr[i]);
                }
                // Set the last position as sentinel.
                arr[n] = CHAR_MAX;
                break;

            case 2:
                printf("Enter the value of k: ");
                scanf("%d", &k);

                if (k > 0 && k <= n) {
                    start = clock();
                    printf("\n  i    j");
                    char result = KthSmallest(arr, n, k);
                    end = clock();
                    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                    printf("\nThe %dth smallest element is %c\n", k, result);
                    printf("Time taken to find the %dth smallest element: %f seconds\n", k, cpu_time_used);
                } else {
                    printf("Invalid value of k\n");
                }
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 3);

    return 0;
}
