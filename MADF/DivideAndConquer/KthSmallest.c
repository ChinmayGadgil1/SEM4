# include<stdio.h>
#include<limits.h>
#include<time.h>

void interchange(int arr[],int i,int j){
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}

int partition(int arr[],int low, int high) {
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

        printf("\n%3d  %3d  ", i + 1, j + 1);
    
        if (i < j) {
            interchange(arr,i,j);
        }
    } while (i < j);
    int temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;
        printf("\n%3d  %3d  ", i + 1, j + 1);

    return j;
}

int KthSmallest(int arr[],int n,int k){
    int low=0,high=n-1;
    arr[n+1]=INT_MAX;
    do{
        int j=partition(arr,low,high+1);
        if(j==k-1){
            return arr[j];
        }
        else if(j>k-1){
            high=j-1;
        }
        else{
            low=j+1;
        }
    }while(1);
}


int main(){
    int n, k;
    int choice;
    int arr[100];
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
                printf("Enter the number of elements in the array: ");
                scanf("%d", &n);
                printf("Enter the elements of the array:\n");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &arr[i]);
                }
                arr[n] = INT_MAX;
                break;

            case 2:
                printf("Enter the value of k: ");
                scanf("%d", &k);

                if (k > 0 && k <= n) {
                    start = clock();
                    printf("\n  i    j");

                    int result = KthSmallest(arr, n, k);
                    
                    end = clock();
                    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("\nThe %dth smallest element is %d\n", k, result);
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
    } while (choice != 3);


return 0;
}