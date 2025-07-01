#include <stdio.h>
#include<stdlib.h>
#include<limits.h>
void interchange(char *arr, int i, int j)
{
    char tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int partition(char *arr, int low, int high)
{
    char pivot = arr[low];
    int i = low, j = high, k = low;
    do
    {
        do
        {
            i++;
        } while (arr[i] < pivot);
        do
        {
            j--;
        } while (arr[j] > pivot);
        if (i < j)
        {
            interchange(arr, i, j);
        }
    } while (i < j);
    arr[low] = arr[j];
    arr[j] = pivot;
    return j;
}

char kthSmallest(char *arr, int n, int k)
{
    int low = 1, high = n;
    do
    {
        int j = partition(arr, low, high + 1);
        if (j == k)
        {
            return arr[j];
        }
        else if (j < k)
        {
            low = j + 1;
        }
        else
        {
            high = j - 1;
        }
    } while (1);
}

int main()
{
    int n;
    char* arr;
    printf("Enter the number of characters in the array: ");
    scanf("%d", &n);
    arr=(char*)malloc((n+2)*sizeof(char));
    printf("Enter the characters (separated by space):\n");
    for (int i = 1; i <= n; i++)
    {
        scanf(" %c", &arr[i]);
    }
    arr[n+1]=CHAR_MAX;
    int k;
    printf("Enter k:");
    scanf("%d",&k);
    char c=kthSmallest(arr,n,k);
    printf("%c",c);
    return 0;
}