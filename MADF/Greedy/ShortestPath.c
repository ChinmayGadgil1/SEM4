#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include<sys/time.h>


long long current_time_us(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

#define infinity INT_MAX
#define MAX 20
int n;

void create(int cost[MAX][MAX])
{
    int max_edges, origin, destin,weight;
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
        printf("Enter edge %d((-1 -1 -1) to quit): ", i);
        scanf("%d%d%d", &origin, &destin,&weight);
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

void printPath(int pred[], int v, int dest) {
    if (dest == v) {
        printf("%d", v);
        return;
    }
    if (pred[dest] == -1) {
        printf("No path exists");
        return;
    }
    printPath(pred, v, pred[dest]);
    printf(" -> %d", dest);
}

void display(int dist[], bool s[], int n, int pred[], int v) {
    printf("\nSource\tDestination\tDistance\tPath\n");
    printf("------\t-----------\t--------\t----\n");
    
    for (int i = 1; i <= n; i++) {
        if (i != v) {  // Don't print path to itself
            printf("%d\t%d\t\t", v, i);
            if (dist[i] == infinity) {
                printf("INF\t\tNo path\n");
            } else {
                printf("%d\t\t", dist[i]);
                printPath(pred, v, i);
                printf("\n");
            }
        }
    }
    printf("\n");
}

void shortestPath(int v, int cost[MAX][MAX], int dist[], int n) {
    bool s[n + 1];
    int pred[n + 1];  // Add predecessor array
    int u;
    
    // Initialize
    for (int i = 1; i <= n; i++) {
        dist[i] = cost[v][i];
        s[i] = false;
        pred[i] = (cost[v][i] != infinity) ? v : -1;
    }
    
    dist[v] = 0;
    s[v] = true;
    pred[v] = -1;

    for (int i = 2; i <= n; i++) {
        u = selectVertex(dist, s, n);
        s[u] = true;
        
        for (int w = 1; w <= n; w++) {
            if (!s[w] && cost[u][w] != infinity) {
                if (dist[w] > dist[u] + cost[u][w]) {
                    dist[w] = dist[u] + cost[u][w];
                    pred[w] = u;  // Update predecessor
                }
            }
        }
    }
    
    // Final path display
    display(dist, s, n, pred, v);
}
int main()
{
    int cost[MAX][MAX] = {infinity};
    int dist[MAX];
    long long start;

    long long end;
   
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
            start=current_time_us();
            shortestPath(v, cost, dist, n);
            end=current_time_us();
            printf("\nTime taken: %lldμs\n", end - start);
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




