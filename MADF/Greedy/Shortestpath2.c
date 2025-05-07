#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include <time.h>
#include <limits.h>
#define MAX_VERTICES 100
void print(int v, int pred[MAX_VERTICES],
           double dist[MAX_VERTICES], int n)
{
    printf("Source\tDestination\tCost\t\tPath\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d\t %d", 1, i + 1);
        if (dist[i] != INT_MAX)
        {
            printf("\t\t%0.2lf\t", dist[i]);
            printf(" %d", i + 1);
            int pred_vertex = pred[i];
            while (pred_vertex != -1)
            {
                printf(" <- %d", pred_vertex + 1);
                pred_vertex = pred[pred_vertex];
            }
            if (dist[i] != 0)
                printf(" <- %d", v + 1);
        }
        else
        {
            printf("INF\tNo path");
        }
        printf("\n");
    }
}
void display_iteration(double
                           dist[MAX_VERTICES],
                       bool S[MAX_VERTICES],
                       int n, int u, int num, int pred[])
{
    int count = 0;
    printf("Iteration %d: u = %d\n", num, u + 1);
    for (int i = 0; i < n; i++)
    {
        if (S[i] == true)
        {
            if (u == i)
                printf("\033[1m|S[%d]|=\033[m", u +
                                                    1);
            else
                printf("S[%d]= ", i + 1);
        }
    }
    printf("True\n");
    for (int i = 0; i < n; i++)
    {
        if (S[i] == false)
        {
            count++;
            printf("S[%d]= ", i + 1);
        }
    }
    if (count != 0)
        printf("False\n\n ");
    for (int i = 0; i < n; i++)
        printf(" dist[%d] ", i + 1);
    printf("\n ");
    for (int i = 0; i < n; i++)
    {
        if (dist[i] != INT_MAX)
        {
            if (S[i] == true)
                printf(" \033[1m%0.2lf[m", dist[i]);
            else
                printf(" %0.2lf\t", dist[i]);
        }
        else
            printf(" INF ");
    }
    printf("\n\n");
}
void ShortestPaths(int u, int cost[MAX_VERTICES][MAX_VERTICES], double dist[MAX_VERTICES], int n, int pred[MAX_VERTICES])
{
    bool S[MAX_VERTICES] = {false};
    int i, num, w;
    for (i = 0; i < n; i++)
    {
        S[i] = false;
        dist[i] = cost[u][i];
        pred[i] = -1;
    }
    dist[u] = 0.0;
    S[u] = true;
    display_iteration(dist, S, n, u, 1, pred);
    for (num = 2; num <= n - 1; num++)
    {
        int minDist = INT_MAX;
        int u = -1;
        for (i = 0; i < n; i++)
        {
            if (!S[i] && dist[i] < minDist)
            {
                minDist = dist[i];
                u = i;
            }
        }
         S[u] = true;
        for (w = 0; w < n; w++)
        {
            if (!S[w] && dist[w] > dist[u] +
                                       cost[u][w])
            {
                dist[w] = dist[u] + cost[u][w];
                pred[w] = u;
            }
        }
        display_iteration(dist, S, n, u, num, pred);
    }
}
int main()
{
    int n, m, u, v, w, i, j, choice;
    int cost[MAX_VERTICES][MAX_VERTICES];
    double dist[MAX_VERTICES];
    int pred[MAX_VERTICES];
    printf("\nAarambh Kavlekar \n23B-CO002\n");
    do
    {
        printf("\nMenu:\n");
        printf("1. Enter graph data\n");
        printf("2. Calculate shortest paths\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter number of vertices: ");
            scanf("%d", &n);
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < n; j++)
                {
                    cost[i][j] = INT_MAX;
                }
            }
            printf("Enter number of edges: ");
            scanf("%d", &m);
printf("Enter the edges (u v w) where u and v are vertices and w is the cost:\n");
for (i = 0; i < m; i++) {
                scanf("%d %d %d", &u, &v, &w);
                cost[u - 1][v - 1] = w;
}
break;
case 2:
printf("Enter source vertex: ");
scanf("%d", &u);
u--;
int min;
clock_t start, end;
start = clock();
ShortestPaths(u, cost, dist, n,pred);
end = clock();
double time_taken = (end - start) +
(end - start) / 1e9;
print(0, pred, dist, n);
printf("\nTime taken: %.9f s\n",
time_taken);
break;
case 3:
break;
default:
printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
    return 0;
}