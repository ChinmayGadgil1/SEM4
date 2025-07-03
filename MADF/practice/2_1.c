#include <stdio.h>
#define MAX 100
struct item
{
    float profit;
    float weight;
    int initial_pos;
    float prof_per_weight;
    float x;
} arr[MAX], tmp[MAX];

int sort_method = 0;

void knapsack(int m, int n)
{
    int i;
    for (i = 1; i <= n; i++)
    {
        arr[i].x = 0;
    }
    float u = m;
    for (i = 1; i <= n; i++)
    {
        if (arr[i].weight > u)
        {
            break;
        }
        arr[i].x = 1;
        u -= arr[i].weight;
    }
    if (i <= n)
    {
        arr[i].x = (float)u / arr[i].weight;
    }
}

void merge(int low, int mid, int high)
{
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high)
    {
        if (sort_method == 0)
        {
            if (arr[i].prof_per_weight >= arr[j].prof_per_weight)
            {
                tmp[k] = arr[i];
                i++;
            }
            else
            {
                tmp[k] = arr[j];
                j++;
            }
        }
        else
        {
            if (arr[i].initial_pos < arr[j].initial_pos)
            {
                tmp[k] = arr[i];
                i++;
            }
            else
            {
                tmp[k] = arr[j];
                j++;
            }
        }
        k++;
    }
    if (i <= mid)
    {
        for (int x = i; x <= mid; x++)
        {
            tmp[k] = arr[x];
            k++;
        }
    }
    else if (j <= high)
    {
        for (int x = j; x <= high; x++)
        {
            tmp[k] = arr[x];
            k++;
        }
    }
    for (int i = low; i <= high; i++)
    {
        arr[i] = tmp[i];
    }
}

void mergesort(int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergesort(low, mid);
        mergesort(mid + 1, high);
        merge(low, mid, high);
    }
}

void display(int n)
{
    double total_profit = 0, total_weight = 0;
    printf("Items: \n");
    printf("   ");
    for (int i = 1; i <= n; i++)
    {
        printf("[%02d]  ", arr[i].initial_pos);
        total_profit += arr[i].profit * arr[i].x;
        total_weight += arr[i].weight * arr[i].x;
    }
    printf("\n");
    printf("X: ");
    for (int i = 1; i <= n; i++)
    {
        printf("%.2lf  ", arr[i].x);
    }
    printf("\nTotal profit: %.2lf\tTotal weight: %.2lf\n", total_profit, total_weight);
}

int main()
{

    int m, n, choice;
    printf("Enter knapsack capacity: ");
    scanf("%d", &m);
    printf("Enter number of arr: ");
    scanf("%d", &n);
    printf("Enter weights: ");
    for (int i = 1; i <= n; i++)
    {
        scanf("%f", &arr[i].weight);
    }

    printf("Enter profits: ");
    for (int i = 1; i <= n; i++)
    {
        scanf("%f", &arr[i].profit);
    }
    for (int i = 1; i <= n; i++)
    {
        arr[i].prof_per_weight = (float)arr[i].profit / arr[i].weight;
        arr[i].initial_pos = i;
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%f ", arr[i].prof_per_weight);
    }
    printf("\n");

    printf("\nMost Optimal solution:\n");
    mergesort(1, n);
    for (int i = 1; i <= n; i++)
    {
        printf("%f ", arr[i].prof_per_weight);
    }
    printf("\n");
     for (int i = 1; i <= n; i++)
    {
        printf("%d ", arr[i].initial_pos);
    }
    printf("\n");
    knapsack(m, n);
    sort_method = 1;
    mergesort(1, n);
      for (int i = 1; i <= n; i++)
    {
        printf("%d ", arr[i].initial_pos);
    }
    printf("\n");
    display(n);

    return 0;
}