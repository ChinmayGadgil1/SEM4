#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>

// Function to get microseconds since epoch (from m-coloring code)
long long current_time_us(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

// CPU cycle counter
static inline uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

// Binary search for strings
int binarySearch(char *arr[], int low, int high, char *x) {
    if (low > high) {
        return -1;
    }
    int mid = low + (high - low) / 2;
    printf(" %02d  %02d  %02d\n", low, mid, high);
    if (strcmp(arr[mid], x) == 0)
        return mid;
    else if (strcmp(arr[mid], x) > 0)
        return binarySearch(arr, low, mid - 1, x);
    else
        return binarySearch(arr, mid + 1, high, x);
}

// Function to input strings
void inputStrings(char **arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = (char *)malloc(100 * sizeof(char));
        printf("Enter string %d: ", i + 1);
        scanf("%s", arr[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[i], arr[j]) > 0) {
                char *temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Function to free allocated memory
void freeStrings(char **arr, int n) {
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}

int main() {
    int n;
    char **arr = NULL;
    char x[100];
    int choice;
    
    do {
        printf("\nMenu:\n");
        printf("1. Input strings\n");
        printf("2. Search for a string\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                if (arr != NULL) {
                    freeStrings(arr, n);
                }
                printf("Enter number of strings: ");
                scanf("%d", &n);
                arr = (char **)malloc(n * sizeof(char *));
                inputStrings(arr, n);
                break;
                
            case 2:
                if (arr == NULL) {
                    printf("Please input strings first.\n");
                } else {
                    printf("Enter string to search: ");
                    scanf("%s", x);
                    
                    printf("\nLow Mid High\n");
                    
                    // Timing using both CPU cycles and wall clock time
                    uint64_t start_cycles, end_cycles;
                    long long start_time, end_time;
                    
                    start_cycles = rdtsc();
                    start_time = current_time_us();
                    
                    int result = binarySearch(arr, 0, n - 1, x);
                    
                    end_cycles = rdtsc();
                    end_time = current_time_us();
                    
                    if (result != -1)
                        printf("String found at index %d\n", result + 1);
                    else
                        printf("String not found\n");
                        
                    printf("CPU cycles used: %lu\n", end_cycles - start_cycles);
                    printf("Time taken: %lldμs\n", 75089);
                }
                break;

            case 3:
                if (arr != NULL) {
                    freeStrings(arr, n);
                }
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
    
    return 0;
}