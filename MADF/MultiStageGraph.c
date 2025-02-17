#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define infinity INT_MAX
#define MAX 20
int n,k;

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
    printf("Enter number of stages:");
    scanf("%d",&k);
}

int selectVertex(int c[MAX][MAX], int j)
{

    return j;
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

void Fgraph(int c[MAX][MAX],int k,int n,int p[]){
    float cost[MAX]={infinity};
    cost[n]=0.0;
    for (int j = n-1; j >=1; j--)
    {
        int r=selectVertex(c,j);
        
    }
    

}

int main()
{
    int cost[MAX][MAX] = {infinity};
    int p[MAX];
    int choice, mincost, v;
    printf("\n1. Create graph\n");
    printf("2. Find Multi stage shortest path\n");
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
            FGraph(cost,k,n,p);
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
