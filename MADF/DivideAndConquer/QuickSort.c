#include <stdio.h>
#include <limits.h>
#include <time.h>
#define MAX 100

int arr[MAX];
int n;
int front = -1, rear = -1;
int queueArr[MAX];

// Queue operations
int isFull() {
    return rear == MAX - 1;
}

int isEmpty() {
    return front == -1 || front > rear;
}

void insert(int item) {
    if (isFull()) {
        printf("Queue Overflow\n");
        return;
    }
    if (front == -1) {
        front++;
    }
    rear++;
    queueArr[rear] = item;
}

int delete() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        return INT_MIN;
    }
    int item = queueArr[front];
    front++;
    return item;
}


void display() {
    if (isEmpty()) {
        return;
    }
    

    int low = delete();
    int high = delete();
    int pivot = delete();
    int rightLow = delete();
    int rightHigh = delete();
    
  
    printf("Array: ");
    for (int i = 0; i < n; i++) {
        if (i == low) printf("[ ");
        if (i == pivot) printf("] %d [ ", arr[i]);
        else printf("%d ", arr[i]);
        if (i == high) printf("] ");
    }
    printf("\n\n");
}

void interchange(int arr[], int i,int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(int low, int high) {
    int pivot = arr[low];
    int i = low;
    int j = high;
    do {
        do {
            i++;
        } while (arr[i] <= pivot);
        do {
            j--;
        } while (arr[j] > pivot);
        
        if (i < j) {
            interchange(arr,i,j);
        }
    } while (i < j);
    
    arr[low] = arr[j];
    arr[j] = pivot;
    return j;
}

void quicksort(int low, int high) {
    if (low < high) {
        int pivloc = partition(low, high + 1);
        insert(low);          
        insert(high);         
        insert(pivloc);       
        insert(pivloc + 1);   
        insert(high);         
        
        printf("After partition at index %d:\n", pivloc);
        display();
        
        quicksort(low, pivloc - 1);
        quicksort(pivloc + 1, high);
    }
}

void inputArray() {
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    arr[n] = INT_MAX;
}

void displayArray() {
    printf("\nCurrent array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void sortArray() {
    clock_t start, end;
    double cpu_time_used;
    
    printf("\nQuickSort steps:\n");
    printf("Initial array:\n");
    displayArray();
    printf("\n");
    
    start = clock();
    quicksort(0, n - 1);
    end = clock();
    
    printf("Final sorted array:\n");
    displayArray();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken to sort: %f seconds\n", cpu_time_used);
}

int main() {
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Input array\n");
        printf("2. Sort array\n");
        printf("3. Display array\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                inputArray();
                break;
            case 2:
                sortArray();
                break;
            case 3:
                displayArray();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
    
    return 0;
}