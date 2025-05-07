#include <stdio.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 100

int x[MAX] = {0};
int sols = 0;
bool solfound = false;

long long current_time_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

void displayMatrix(int n)
{
    printf("\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (x[i] == j)
            {
                printf("Q%d ", i);
            }
            else
            {
                printf("-- ");
            }
        }
        printf("\n");
    }
}

bool place(int k, int i)
{
    for (int j = 1; j < k; j++)
    {
        if (x[j] == i || abs(x[j] - i) == abs(j - k))
        {
            return false;
        }
    }
    return true;
}

void NQueens(int k, int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (place(k, i))
        {
            x[k] = i;
            if (k == n)
            {
                if (!solfound)
                {
                    for (int j = 1; j <= n; j++)
                    {
                        printf("X[%d]=%d  ", j, x[j]);
                    }
                    displayMatrix(n);
                    solfound=true;
                }
                sols++; 
            }
            else
            {
                NQueens(k + 1, n);
            }
        }
    }
}

int main()
{
    int n, choice;
    do
    {
        printf("\n==== N-Queens Problem ====\n");
        printf("1. Solve N-Queens\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the number of queens: ");
            scanf("%d", &n);
            printf("\nSolutions:\n");
            long long start = current_time_us();
            printf("\n");
            solfound = false;
            sols = 0;
            NQueens(1, n);

            printf("\nTotal solutions: %d\n", sols);
            sols = 0;
            long long end = current_time_us();
            printf("\nTime taken: %lldμs\n", end - start);
            break;
        case 2:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 2);

    return 0;
}
