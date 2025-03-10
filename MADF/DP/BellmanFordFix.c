#include <stdio.h>
#include <limits.h>
#define MAX 100
#define inf 10000

void BellmanFord(int v, int cost[MAX][MAX], int dist[], int n)
{
    int temp[MAX]={inf};
    for (int i = 1; i <= n; i++)
    {
        dist[i] = cost[v][i];
        temp[i]=dist[i];
    }
     printf("\ndist[1] ");
    for (int x = 1; x <=n; x++)
            {

                if (dist[x] == inf)
                {
                    printf("inf ");
                }
                else
                {
                    printf("%3d ", dist[x]);
                }
            }
    for (int k = 2; k <= n - 1; k++)
    {
            printf("\ndist[%d] ", k);
        for (int u = 1; u <= n; u++)
        {
            if (u == v)
                continue;
            for (int i = 1; i <= n; i++)
            {
                if (dist[u] > dist[i] + cost[i][u])
                {
                    temp[u] = dist[i] + cost[i][u];
                }
            }
            for(int i=1;i<=n;i++)
                dist[i]=temp[i];
            
        }
            for (int x = 1; x <=n; x++)
            {

                if (dist[x] == inf)
                {
                    printf("inf ");
                }
                else
                {
                    printf("%3d ", dist[x]);
                }
            }
    }
}

int main()
{
    int n=7;
    int cost[MAX][MAX]={inf};
    int graph[8][8]={
            {inf,inf,inf,inf,inf,inf,inf,inf},
        {inf,0,6,5,5,inf,inf,inf},
        {inf,inf,0,3,inf,-1,2,3},
        {inf,inf,-2,0,inf,1,inf,inf},
        {inf,-2,3,-2,0,inf,-1,inf},
        {inf,1,2,inf,inf,0,5,3},
        {inf,4,1,inf,inf,inf,0,3},
        {inf,-2,-1,3,inf,inf,-2,0}
    };

    for (int i = 1; i <= n+1; i++)
    {
        for (int j= 1; j <=n+1; j++)
        {
            cost[i][j]=graph[i][j];
        }
    }
    int dist[MAX];
    BellmanFord(1,cost,dist,n);
    printf("\n");
    return 0;
}
