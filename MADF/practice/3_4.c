#include <stdio.h>
#define MAX 100
#define inf 99999
int n;
int k;
int G[MAX][MAX];

int select(int j,int *cost){
    
    int min_cost = inf;
    int min_vertex = -1;
    
    for(int r = j+1; r <= n; r++) {
        if(G[j][r] != inf && cost[r] != inf) {
            int current_cost = G[j][r] + cost[r];
            if(current_cost < min_cost) {
                min_cost = current_cost;
                min_vertex = r;
            }
        }
    }
    return min_vertex;
}


void createGraph()
{
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of stages: ");
    scanf("%d", &k);
    int max_edges = n * (n - 1);
    int origin, destin, weight;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == j && (i != 0 && j != 0))
                G[i][j] = 0;
            else
                G[i][j] = inf;
        }
    }
    printf("(-1,-1) to quit\n");
    printf("Enter edges and weight: \n");
    for (int i = 1; i <= max_edges; i++)
    {
        scanf("%d%d%d", &origin, &destin, &weight);
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
            G[origin][destin] = weight;
        }
    }
}

void fgraph(){
    int stage[n],p[k+1];
    int d[MAX]={0};
    stage[1]=1;
    stage[n]=k;
    int cost[MAX];
    for(int i=1;i<=n;i++){
        cost[i]=inf;
    }
    cost[n]=0;

    for(int j=n-1;j>=1;j--){
        int r=select(j,cost);
        cost[j]=G[j][r]+cost[r];
        stage[j]=stage[r]-1;
        d[j]=r;
        printf("cost[%d,%d]=%d\td[%d,%d]=%d\n",stage[j],j,cost[j],stage[j],j,d[j]);
    }

    p[1]=1;
    p[k]=n;

    for(int i=2;i<k;i++){
        p[i]=d[p[i-1]];
    }
    for (int i = 1; i <=k; i++)
    {
        printf("%d ",p[i]);
    }
    
}


int main()
{
    createGraph();
    fgraph();
    return 0;
}