#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define inf INT_MAX
#define MAX 20
int n,k;

void create(int cost[MAX][MAX])
{
    int max_edges, origin, destin;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    max_edges = n * (n - 1);
    printf("Enter number of stages:");
    scanf("%d",&k);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cost[i][j] = inf;
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


int selectVertex(int c[MAX][MAX], int j,int cost[MAX])
{
    int min = j;
    int r;
    for(r=j;r<=n;r++){
        if(c[j][r]<inf && c[j][r]+cost[r]<c[j][min]+cost[min]){
            min=r;
        }
    }
    return min;
}

void Fgraph(int c[MAX][MAX],int k,int n,int p[]){
    int cost[MAX]={inf};
    int d[MAX]={0};
    int mincost=0;
    cost[n]=0;
    float x=(float)k-(1/(k-1));
    int stage=k-1;
    for (int j = n-1; j >=1; j--)
    {
        x-=0.25;
        stage=x;
        int r=selectVertex(c,j,cost);
        cost[j]=c[j][r]+cost[r];
        printf("Cost(%02d,%02d)=%02d  ",stage,j,cost[j]);
        printf("r(%02d,%02d)=%02d\n",stage,j,r);
        d[j]=r; 
        
    }
    p[1]=1;
    p[k]=n;
    for (int j = 2; j <=k-1; j++)
    {
        p[j]=d[p[j-1]];
    }
    printf("Shortest path is: ");

    printf("%d",p[1]);
    for (int i = 2; i <= k; i++)
    {
        printf("->%d",p[i]);
    }
    printf("\nMincost=%d\n",cost[1]);
}

int selectVertexB(int c[MAX][MAX], int j,int bcost[MAX])
{
    int min = j;
    int r;
    for(r=j;r>=1;r--){
        if(c[r][j]<inf && c[r][j]+bcost[r]<c[min][j]+bcost[min]){
            min=r;
        }
    }
    return min;
}
void Bgraph(int c[MAX][MAX],int k,int n,int p[]){
    int bcost[MAX]={inf};
    int d[MAX]={0};
    int mincost=0;
    bcost[1]=0;
    float x=(float)k-(1/(k-1));
    int stage=k-1;
    for (int j = 2; j <=n-1; j++)     
    {
        int r=selectVertexB(c,j,bcost);
        bcost[j]=c[r][j]+bcost[r];
        printf("Cost=%02d  ",bcost[j]);
        printf("r=%02d\n",r);
        d[j]=r; 
    }
    p[1]=1;
    p[k]=n;
    for (int j = k-1; j >=2; j--)
    {
        p[j]=d[p[j+1]];
    }
    printf("Shortest path is: ");
    printf("%d",p[1]);
    for (int i = 2; i <= k; i++)
    {
        printf("->%d",p[i]);
    }
    printf("\nMincost=%d\n",bcost[n]);
}

int main()
{
    int cost[MAX][MAX] = {inf};
    int p[MAX];
    int choice, mincost, v;
    int graph[15][15] = {
        {inf},
        {inf,inf,9,8,6,7,inf,inf,inf,inf,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,10,11,12,inf,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,15,inf,14,13,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,inf,10,11,12,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,8,9,inf,10,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,5,6,inf,7,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,8,9,7,inf,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,6,7,8,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,5,inf,8,6,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,8},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,9},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,8},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,7},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},
    };
    n=14;
    // printf("C[1][5]=%d\n",graph[1][5]+graph[5][6]+graph[6][10]+graph[10][14]);
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            cost[i][j] = graph[i][j];
        }
    }
    Fgraph(cost,5,14,p);
    printf("\n");
    Bgraph(cost,5,14,p);
    return 0;
}
