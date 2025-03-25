#include <stdio.h>
#define MAX 100
#define inf 1000000
#include <sys/time.h>

long long current_time_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

struct Item
{
    double weight;
    double profit;
    double profit_per_weight;
    double x;
    int index;
};

struct Item items[MAX];

void Knapsack(int m, int n)
{
    for (int i = 0; i < n; i++)
    {
        items[i].x = 0;
    }

    int u = m, i;
    for (i = 0; i < n; i++)
    {
        if (items[i].weight > u)
            break;
        items[i].x = 1.0;
        u -= items[i].weight;
    }
    if (i < n)
    {
        items[i].x = (double)u / items[i].weight;
    }
}

void sort(struct Item items[], int n)
{
    struct Item temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (items[i].profit_per_weight < items[j].profit_per_weight)
            {
                temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

void desort(struct Item items[], int n)
{
    struct Item temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (items[i].index > items[j].index)
            {
                temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

void display(struct Item items[], int n)
{
    double total_profit = 0, total_weight = 0;
    printf("Items: \n");
    printf("   ");
    for (int i = 0; i < n; i++)
    {
        printf("[%02d]  ", items[i].index);
        total_profit += items[i].profit * items[i].x;
        total_weight += items[i].weight * items[i].x;
    }
    printf("\n");
    printf("X: ");
    for (int i = 0; i < n; i++)
    {
        printf("%.2lf  ", items[i].x);
    }
    printf("\nTotal profit: %.2lf\tTotal weight: %.2lf\n", total_profit, total_weight);
}

void sortByProfit(struct Item items[], int n)
{
    struct Item temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (items[i].profit < items[j].profit)
            {
                temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

void sortByWeight(struct Item items[], int n)
{
    struct Item temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (items[i].weight > items[j].weight)
            {
                temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

int main()
{
    int m, n, choice;
    long long start_time, end_time;
    printf("Enter knapsack capacity: ");
    scanf("%d", &m);
    printf("Enter number of items: ");
    scanf("%d", &n);

    while (1)
    {
        printf("\nMenu\n");
        printf("1. Enter weights and profits\n");
        printf("2. Highest Profit solution\n");
        printf("3. Lowest Weight solution\n");
        printf("4. Most Optimal solution\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Enter weights: ");
            for (int i = 0; i < n; i++)
            {
                scanf("%lf", &items[i].weight);
            }

            printf("Enter profits: ");
            for (int i = 0; i < n; i++)
            {
                scanf("%lf", &items[i].profit);
            }
            for (int i = 0; i < n; i++)
            {
                items[i].profit_per_weight = items[i].profit / items[i].weight;

                items[i].index = i;
            }
        }
        else if (choice == 2)
        {
            start_time = current_time_us();
            // Highest Profit
            printf("\nHighest Profit solution:\n");
            sortByProfit(items, n);
            Knapsack(m, n);
            desort(items, n);
            display(items, n);
            end_time = current_time_us();
            printf("Time taken: %lld microseconds\n", end_time - start_time);
        }
        else if (choice == 3)
        {
            // Lowest Weight
            start_time = current_time_us();
            printf("\nLowest Weight solution:\n");
            sortByWeight(items, n);
            Knapsack(m, n);
            desort(items, n);
            display(items, n);
            end_time = current_time_us();
            printf("Time taken: %lld microseconds\n", end_time - start_time);
        }
        else if (choice == 4)
        {
            // Optimal
            start_time = current_time_us();
            printf("\nMost Optimal solution:\n");
            sort(items, n);
            Knapsack(m, n);
            desort(items, n);
            display(items, n);
            end_time = current_time_us();
            printf("Time taken: %lld microseconds\n", end_time - start_time);
        }
        else if (choice == 5)
        {
            return 0;
        }
        else
        {
            printf("Invalid choice\n");
        }
    }

    return 0;
}
