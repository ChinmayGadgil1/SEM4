#include <stdio.h>
#include <sys/time.h>
#define TRUE 1
#define FALSE 0
#define MAX 20

long long current_time_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

int n, solutionCount = 0, nodeCount = 0;
int G[MAX][MAX], x[MAX];

void createGraph()
{
    int origin, destination;
    int max_edges = n * (n - 1);
    printf("Enter the edges (origin, destination) (-1,-1 to exit):\n");
    for (int i = 1; i <= max_edges; i++)
    {
        scanf("%d%d", &origin, &destination);
        if ((origin == -1) && (destination == -1))
        {
            break;
        }
        if (origin > n || destination > n || origin < 1 || destination < 1)
        {
            printf("Invalid edge! Please enter values between 1 and %d\n", n);
            i--;
        }
        else
        {
            G[origin][destination] = 1;
            G[destination][origin] = 1;
        }
    }
}

void nextValue(int k, int m)
{
    int j, i;
    do
    {
        x[k] = (x[k] + 1) % (m + 1);
        if (x[k] == 0)
        {
            return;
        }
        for (j = 1; j <= n; j++)
        {
            if (G[k][j] == 1 && x[k] == x[j])
            {
                break;
            }
        }
        if (j == n + 1)
        {
            break;
        }
    } while (TRUE);
}
void nextValueOriginal(int k, int m)
{
    int j, i;
    do
    {
        x[k] = (x[k] + 1) % (m + 1);
        if (x[k] == 0)
        {
            return;
        }
        for (j = 1; j <= n; j++)
        {
            if (G[k][j] == 1 && x[k] == x[j])
            {
                printf("Leaf Node %3d : ", ++nodeCount);
                for (i = 1; i <= k; i++)
                    printf("x[%d] = %d ", i, x[i]);
                printf(" (Bound)\n");
                break;
            }
        }
        if (j == n + 1)
        {
            break;
        }
    } while (TRUE);
}

void graphColoring(int k, int m)
{
    int i, checked = 0;
    do
    {
        nextValue(k, m);
        if (x[k] == 0)
            return;
        if (k == n)
        {
            if (!checked)
            {
                ++solutionCount;
                checked = 1;
            }
        }
        else
            graphColoring(k + 1, m);
    } while (TRUE);
}
void graphColoringOrginal(int k, int m)
{
    int i, checked = 0;
    do
    {
        nextValueOriginal(k, m);
        if (x[k] == 0)
            return;
        if (k == n)
        {
            if (!checked)
            {
                ++solutionCount;
                printf("\e[1mLeaf node %3d : \e[m", ++nodeCount);
                for (i = 1; i <= n; i++)
                {
                    printf("\e[1mx[%d] = %d \e[m", i, x[i]);
                }
                printf("\tSolution Vector found!(Solution %d)", solutionCount);
                printf("\n");
                checked = 1;
            }
        }
        else
            graphColoringOrginal(k + 1, m);
    } while (TRUE);
}

int main()
{
    int choice;
    do
    {
        printf("\nGraph Coloring Menu\n");
        printf("1. Input Graph \n2. Find Coloring\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int i, j, max = 0, m;
            // Reset global variables
            solutionCount = 0;
            nodeCount = 0;
            // Reset arrays
            for (i = 0; i < MAX; i++)
            {
                x[i] = 0;
                for (j = 0; j < MAX; j++)
                {
                    G[i][j] = 0;
                }
            }

            printf("Enter the number of vertices in the graph : ");
            scanf("%d", &n);
            for (i = 1; i <= n; i++)
                x[i] = 0;

            createGraph();

            printf("The adjacency matrix of the graph is : \n");
            for (i = 1; i <= n; i++)
            {
                for (j = 1; j <= n; j++)
                {
                    printf("%d ", G[i][j]);
                    if (G[i][j] == 1)
                    {
                        if (max < j)
                            max = j;
                    }
                }
                printf("\n");
            }
            break;
        case 2:
            m = 0;
            for (i = 1; i <= n; i++)
            {
                for (j = 1; j <= n; j++)
                {
                    if (G[i][j] == 1)
                    {
                        if (m < j)
                            m = j;
                    }
                }
            }

            printf("The degree of the graph is : %d\n", ++m - 1);
            for (i = 1; i <= m; i++)
            {
               
                graphColoring(1, i);

                

                if (solutionCount != 0)
                {
                    solutionCount = 0;
                    nodeCount = 0;

                    long long start = current_time_us();
                    graphColoringOrginal(1, i);
                    long long end = current_time_us();
                printf("\nTime taken: %lldμs\n", end - start);
                    printf("\nThe number of solutions is : %d\n", solutionCount);
                    printf("The chromatic number of the graph is %d\n", i);
                    break;
                }
                for (j = 1; j <= n; j++)
                    x[j] = 0;
            }
            break;
        }
        case 3:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}