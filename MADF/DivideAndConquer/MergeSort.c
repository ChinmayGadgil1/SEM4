#include <stdio.h>
#include <time.h>
#define MAX 100

struct record {
    int id;
    char name[100];
    int age;
};

struct record a[MAX], b[MAX];

void Merge(int low, int mid, int high) {
    int i = low, j = mid + 1, k = low, x;
    while (i <= mid && j <= high) {
        if (a[i].id <= a[j].id) {
            b[k++] = a[i++];
        } else {
            b[k++] = a[j++];
        }
    }
    if (i <= mid) {
        for (x = i; x <= mid; x++) {
            b[k++] = a[x];
        }
    } else {
        for (x = j; x <= high; x++) {
            b[k++] = a[x];
        }
    }
    for (k = low; k <= high; k++) {
        a[k] = b[k];
    }
}

void MergeSort(int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        MergeSort(low, mid);
        MergeSort(mid + 1, high);
        Merge(low, mid, high);
    }
}

int main() {
    int i, n, choice;
    time_t start, end;
    double cpu_time_used;

    do {
        printf("\n1.Create Records\n2.Display Records\n3.Sort Records\n4.Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\nEnter number of records: ");
                scanf("%d", &n);
                printf("Enter id, name and age:\n");
                for (i = 0; i < n; i++) {
                    scanf("%d %s %d", &a[i].id, a[i].name, &a[i].age);
                }
                break;
            case 2:
                printf("\nRecords are:\n");
                for (i = 0; i < n; i++) {
                    printf("%d\t%s\t%d\n", a[i].id, a[i].name, a[i].age);
                }
                break;
            case 3:
                time(&start);
                MergeSort(0, n - 1);
                time(&end);
                cpu_time_used = difftime(end, start);
                printf("\nRecords sorted successfully!\n");
                printf("Time taken to sort: %f seconds\n", cpu_time_used);
                break;
            case 4:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
