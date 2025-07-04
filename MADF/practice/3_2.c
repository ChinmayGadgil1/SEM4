# include<stdio.h>
#include<stdlib.h>
#define MAX 20
#define inf 100000

int cost[MAX][MAX];
int n;
int dist[MAX][MAX];
int p[MAX]={0};


void create(){
    int max_edges,org,dest,weight;
    printf("Enter number of vertices:");
    scanf("%d",&n);
    max_edges=n*(n-1);
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            cost[i][j]=inf;
        }
    }    
    for (int i = 0; i < MAX; i++)
    {
        cost[i][i]=0;
    }
    printf("Enter edges:\n");
    for (int i = 0; i < max_edges; i++)
    {
        scanf("%d%d%d",&org,&dest,&weight);
        if(org==-1 && dest==-1)break;
        if(org<1 || dest<1 || org>n|| dest>n){
            printf("Invalid edge\n");
            i--;
        }
        cost[org][dest]=weight;
    }
    
}

int bellmanFord(int v){
    for(int i=1;i<=n;i++){
        dist[1][i]=cost[v][i];
        p[i]=v;
    }
    for(int k=2;k<n;k++){
        for(int x=1;x<=n;x++){
            dist[k][x]=dist[k-1][x];
        }
        for(int u=1;u<=n;u++){
            if(u==v) continue;
            for(int i=1;i<=n;i++){
                if(dist[k][u]>dist[k-1][i]+cost[i][u]){
                    dist[k][u]=dist[k-1][i]+cost[i][u];
                    p[u]=i;
                }
            }
        }
    }
}

void printPath(int v,int i){
    if(v==i){
        printf("%d",v);
        return;
    }
    printPath(v,p[i]);
    printf("->%d",i);
}

int main(){
int v=1;
create();
bellmanFord(v);

for(int i=1;i<=n;i++){
    printPath(v,i);
    printf("\n");
}

return 0;
}