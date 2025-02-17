#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define infinity INT_MAX
#define MAX 20
int n;

void create(int cost[MAX][MAX])
{
    int max_edges, origin, destin;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    max_edges = n * (n - 1);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cost[i][j] = infinity;
        }
    }

    for (int i = 1; i <= max_edges; i++)
    {
        printf("Enter edge %d((-1 -1) to quit): ", i);
        scanf("%d%d", &origin, &destin);
        if ((origin == -1) && (destin == -1))
        {
            break;
        }
        if (origin > n || destin > n || origin < 1 || destin < 1)
        {
            printf("Invalid edge\n");
            i--;
        }
        else
        {
            printf("Enter cost: ");
            int weight;
            scanf("%d", &weight);
            cost[origin][destin] = weight;
        }
    }
}

int selectVertex(int dist[], bool s[], int n)
{

    int i = 1;
    while (s[i] == true)
        i++;
    int minIndex = i;

    while (i <= n)
    {

        if (s[i] == false && dist[i] < dist[minIndex])
        {
            minIndex = i;
        }
        i++;
    }
    return minIndex;
}
void display(int dist[],bool s[], int n)
{
    bool flag=false;
    printf("\n");
    for (int i = 1; i <=n; i++)
    {
        if(s[i]==true){
            printf("s[%d]=",i);
            flag=true;
        }
    }
    if(flag)
        printf("true\n");

    flag=false;
    for (int i = 1; i <=n; i++)
    {
        if(s[i]==false){
            printf("s[%d]=",i);
            flag=true;
        }
    }
    if(flag)
        printf("false\n\n");

    
    for (int i = 1; i <= 4; i++)
    {
        if (dist[i] == infinity)
        {
            printf("dist[%d]=inf ",i);
        }
        else
        {
            printf("dist[%d]=%-3d ",i, dist[i]);
        }
        if (dist[2 * i] == infinity)
        {
            printf("   dist[%d]=inf\n",2*i);
        }
        else
        {
            printf("   dist[%d]=%-3d\n",2*i, dist[2*i]);
        }
    }
    printf("\n");
}
void shortestPath(int v, int cost[MAX][MAX], int dist[], int n)
{
    bool s[n + 1];
    int u;
    for (int i = 1; i <= n; i++)
    {
        dist[i] = cost[v][i];
        s[i] = false;
    }
    printf("\nStep1\n");
    display(dist,s, n);
    dist[v] = 0;
    s[v] = true;
    for (int i = 2; i <= n; i++)
    {
        u = selectVertex(dist, s, n);
        s[u] = true;
        for (int w = 1; w <= n; w++)
        {
            if (cost[u][w] != infinity && s[w] == false)
            {
                if (dist[w] > dist[u] + cost[u][w])
                {
                    dist[w] = dist[u] + cost[u][w];
                }
            }
        }
        display(dist,s, n);
    }
}

int main()
{
    int cost[MAX][MAX] = {infinity};
    n = 8;
    int test[9][9] = {
        {infinity, infinity, infinity, infinity, infinity, infinity, infinity, infinity, infinity},
        {infinity, infinity, 20, 40, infinity, 50, 40, infinity, infinity},
        {infinity, infinity, infinity, 15, 10, 5, infinity, infinity, infinity},
        {infinity, infinity, infinity, infinity, infinity, infinity, infinity, infinity, 5},
        {infinity, infinity, infinity, 2, infinity, infinity, 8, infinity, infinity},
        {infinity, infinity, infinity, infinity, 3, infinity, infinity, 8, infinity},
        {infinity, infinity, infinity, 3, infinity, 6, infinity, infinity, 4},
        {infinity, infinity, 3, infinity, infinity, infinity, 2, infinity, 2},
        {infinity, infinity, 3, infinity, infinity, 2, infinity, infinity, infinity}};

    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            cost[i][j] = test[i][j];
        }
    }

    int dist[MAX];

    int choice, mincost, v;
    printf("\n1. Create graph\n");
    printf("2. Find shortest path\n");
    printf("3. Exit\n");

    while (1)
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            create(cost);
            break;
        case 2:
            printf("Enter start vertex:");
            scanf("%d", &v);
            shortestPath(v, cost, dist, n);
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice\n");
            break;
        }
    }

    return 0;
}