# include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#define MAX 20
#define inf 1000000
bool S[MAX];
int dist[MAX];
int cost[MAX][MAX];
int pred[MAX];
int n,v;

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

int select(){
    int firstFalseIndex=1;
    for (int i = 1; i <=n  ; i++)
    {
        if(S[i]==false){
            firstFalseIndex=i;
            break;
        }
    }
    
    int min=firstFalseIndex;
    for (int i = 1; i <=n; i++)
    {
        if(dist[i]<dist[min] && S[i]==false){
            min=i;
        }
    }
    return min;
}

void SSSP(int v){
    for (int i = 1; i <=n; i++)
    {
        S[i]=false;
        dist[i]=cost[v][i];
        if(cost[v][i]!=inf){
            pred[i]=v;
        }
        else{
            pred[i]=-1;
        }
    }
    int u;
    S[v]=true;
    dist[v]=0;
    pred[v]=-1;
    for (int i = 2; i <= n; i++)
    {
        u=select();
        S[u]=true;
        for (int w = 1; w <= n; w++)
        {
            if(S[w]==false && dist[u]+cost[u][w]<dist[w]){
                dist[w]=dist[u]+cost[u][w];
                pred[w]=u;
            }
        }
    }    
}

void printpath(int i){
    if(i==v){
        printf("%d",v);
        return;
    } 
    printpath(pred[i]);
    printf("->%d",i);
}

int main(){
v=1;
create();
SSSP(v);
for (int  i = 1; i <=n; i++)
{
    printf("%d ",dist[i]);
    printpath(i);
    printf("\n");
}

return 0;
}