#include <stdio.h>
#include <limits.h>
#include <math.h>
#define MAX 1000

int arr[MAX], n;
int front = -1, rear = -1;

int queueArr[MAX];

int isFull()
{
    return rear == MAX - 1;
}

int isEmpty()
{
    return front == -1 || front > rear;
}

void insert(int item)
{
    if (isFull())
    {
        printf("Queue Overflow\n");
        return;
    }
    if (front == -1)
    {
        front++;
    }

    rear++;
    queueArr[rear] = item;
}

int delete()
{
    if (isEmpty())
    {
        printf("Queue Underflow\n");
        return INT_MIN;
    }
    int item = queueArr[front];
    front++;
    return item;
}

void MinMax(int i, int j, int *min, int *max)
{
    if (i == j)
    {
        *max = *min = arr[i];
        printf("\n%3d  %3d  %3d  %3d", i + 1, j + 1, *min, *max);
    }
    else if (i == j - 1)
    {
        if (arr[i] > arr[j])
        {
            *max = arr[i];
            *min = arr[j];
            printf("\n%3d  %3d  %3d  %3d", i + 1, j + 1, *min, *max);
        }
        else
        {
            *max = arr[j];
            *min = arr[i];
            printf("\n%3d  %3d  %3d  %3d", i + 1, j + 1, *min, *max);
        }
    }
    else
    {
        int mid = (i + j) / 2;
        int min1, max1;

        // insert(i);
        // insert(mid);
        // insert(mid + 1);
        // insert(j);
        MinMax(i, mid, min, max);
        MinMax(mid + 1, j, &min1, &max1);
        if (*min > min1)
        {
            *min = min1;
        }
        if (*max < max1)
        {
            *max = max1;
        }
        printf("\n%3d  %3d  %3d  %3d", i + 1, j + 1, *min, *max);
    }
}

// void display()
// {
//     // int levels = log2(top + 1 / 2);
//     int low, high;
//     // for (int i = 0; i < levels; i++)
//     // {
//     //     for (int k = 0; k < pow(2, i); k++)
//     //     {
//     //         low = delete();
//     //         high = delete();
//     //         for (int j = low; j <= high; j++)
//     //         {
//     //             printf("%d ", arr[j]);
//     //         }
//     //         printf(" ");
//     //     }
//     //     printf("\n");
//     // }
//     int levelCount = 1;
//     while (1)
//     {
//         printf("\n\n");

//         if (isEmpty())
//             return;

//         for (int k = 0; k < n - levelCount; k++)
//         {
//             printf(" ");
//         }
//         for (int i = 0; i < levelCount; i++)
//         {
//             if (isEmpty())
//                 return;
//             low = delete ();
//             high = delete ();

//             for (int j = low; j <= high; j++)
//             {
//                 printf("%d  ", arr[j]);
//             }
//             printf("   ");
//         }
//         levelCount *= 2;
//     }
//     printf("\n");
// }

void display()
{
    printf("\n\n");

    int low, high, mid, levCount;
    low = 0, high = n - 1;
    mid = (low + high) / 2, levCount = 1;
    insert(low);
    insert(high);
    while (!isEmpty())
    {
        for (int k = 0; k < n - levCount; k++)
        {
            printf(" ");
        }
        for (int j = 0; j < levCount; j++)
        {
            if(isEmpty()) return;
            low = delete ();
            high = delete ();
            for (int i = low; i <= high; i++)
            {
                printf("%d  ", arr[i]);
            }
            mid = (low + high) / 2;
            if (low<mid)
            {
                insert(low);
                insert(mid);
            }
            if(mid<high && low!=mid){
                insert(mid + 1);
                insert(high);
            }
            printf("  ");
        }
        printf("\n\n");
        levCount *= 2;
    }
    printf("\n\n");
}

int main()
{

    int choice;
    do
    {
        printf("\nMenu:\n");
        printf("1. Input array\n");
        printf("2. Find Min and Max\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the number of elements: ");
            scanf("%d", &n);

            printf("Enter the elements: ");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &arr[i]);
            }
            break;

        case 2:
            if (n == 0)
            {
                printf("Array is empty. Please input the array first.\n");
            }
            else
            {
                int min, max;
                printf("\n  i    j   min   max");
                MinMax(0, n - 1, &min, &max);
                printf("\nMinimum: %d\nMaximum: %d\n", min, max);
                display();
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