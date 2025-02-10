#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#define infinity INT_MAX
#define MAX 20
int n;
struct Edge
{
    int origin;
    int destination;
};

void insert(struct Edge E[MAX], int origin, int destin)
{
    if(origin>destin){
        int t=origin;
        origin=destin;
        destin=t;
    }
    int i = 0;
    while (i < MAX && E[i].origin != -1)
    {
        if (E[i].origin > origin || (E[i].origin == origin && E[i].destination > destin))
        {
            break;
        }
        i++;
    }
    for (int j = MAX - 1; j > i; j--)
    {
        E[j] = E[j - 1];
    }
    E[i].origin = origin;
    E[i].destination = destin;
   
}

void create(int cost[MAX][MAX], struct Edge E[MAX])
{
    int max_edges, origin, destin;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    max_edges = n * (n - 1) / 2;

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
            cost[destin][origin] = weight;
            insert(E, origin, destin);
        }
    }
}

struct Edge selectEdge(struct Edge E[MAX], int cost[MAX][MAX], int n)
{
    struct Edge minEdge;
    minEdge.origin = -1;
    minEdge.destination = -1;
    int minCost = infinity;
    for (int i = 1; i <= n; i++)
    {
        if (E[i].origin == -1 && E[i].destination == -1)
        {
            continue;
        }
        if (minCost > cost[E[i].origin][E[i].destination])
        {
            minCost = cost[E[i].origin][E[i].destination];
            minEdge = E[i];
        }
    }
    return minEdge;
}

void displayNear(int* near,int n,int cost[MAX][MAX]){
    printf("\nnear: ");
    for (int i = 1; i <= n; i++)
    {
        printf("[%02d] ", i);
    }
    printf("\n       ");

    for (int i = 1; i <= n; i++)
    {
        
        printf("%2d   ", near[i]);
    }
    printf("\ncost:  ");
    for (int i = 1; i <= n; i++)
    {
        if(cost[i][near[i]]==INT_MAX){
            printf("inf  ");
            continue;
        }
        if(near[i]==0){
            printf("--   ");
            continue;
        }
        printf("%2d   ", cost[i][near[i]]);
    }
    printf("\n");
}

int prims(struct Edge E[MAX], int cost[MAX][MAX], int n, int t[MAX][2])
{
    int near[MAX];
    struct Edge e = selectEdge(E, cost, n);
    int k = e.origin;
    int l = e.destination;
    int mincost = cost[k][l];
    t[0][0] = k;
    t[0][1] = l;
    for (int i = 1; i <= n; i++)
    {
        if (cost[i][l] < cost[i][k])
        {
            near[i] = l;
        }
        else
        {
            near[i] = k;
        }
    }
    near[k] = near[l] = 0;
    displayNear(near,n,cost);
    for (int i = 1; i < n - 1; i++)
    {
        int j;
        int min = infinity;
        for (int k = 1; k <= n; k++)
        {
            if (near[k] != 0 && cost[k][near[k]] < min)
            {
                min = cost[k][near[k]];
                j = k;
            }
        }
        t[i][0] = j;
        t[i][1] = near[j];
        mincost += cost[j][near[j]];
        near[j] = 0;
        for (int k = 1; k <= n; k++)
        {
            if (near[k] != 0 && cost[k][near[k]] > cost[k][j])
            {
                near[k] = j;
            }
        }
        displayNear(near,n,cost);
    }
    
    return mincost;
}

int main()
{

    int cost[MAX][MAX] = {infinity};
    struct Edge E[MAX] = {infinity};
    int t[MAX][2];

    int choice, mincost;
    printf("\n1. Create graph\n");
    printf("2. Find Minimum Spanning Tree\n");
    printf("3. Exit\n");

    while (1)
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            create(cost, E);
            break;
        case 2:
            mincost = prims(E, cost, n, t);
            printf("Mincost: %d\n", mincost);
            for (int i = 0; i < n - 1; i++)
            {
                printf("%d - %d\n", t[i][0], t[i][1]);
            }
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