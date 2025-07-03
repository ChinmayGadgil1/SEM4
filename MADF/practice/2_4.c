# include<stdio.h>
#include<stdlib.h>
#define MAX 20
#define inf 100000
int n;
int cost[MAX][MAX];
int t[MAX][3];
int parent[MAX];
struct Edge{
    int org;
    int dest;
    int weight;
} E[MAX];
int edgeCount=0;
int currEdgeEncountered=1;

void insertEdge(int org,int dest,int weight){
    edgeCount++;
    E[edgeCount].org=org;
    E[edgeCount].dest=dest;
    E[edgeCount].weight=weight;
}

void create(){
    int max_edges,org,dest,weight;
    printf("Enter number of vertices:");
    scanf("%d",&n);
    max_edges=n*(n-1)/2;
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
        cost[dest][org]=weight;
        insertEdge(org,dest,weight);
    }   
}

void sort(){
    for(int i=1;i<=edgeCount;i++){
        for(int j=1;j<=edgeCount-i;j++){
            if(E[j].weight>E[j+1].weight){
                struct Edge tmp=E[j];
                E[j]=E[j+1];
                E[j+1]=tmp;
            }
        }
    }
}

int Parent(int j)
{
    while(parent[j]!=-1){
        j=parent[j];
    }
    return j;
}

int kruskals(){
    for(int i=1;i<=n;i++){
        parent[i]=-1;
    }
    int mincost=0,u,v,j,k,i=1;
    sort();
    for(int i=1;i<=edgeCount;i++){
        printf("%d ",E[i].weight);
    }
    printf("\n");
    while(i<=n-1){
        u=E[currEdgeEncountered].org;
        v=E[currEdgeEncountered].dest;
        currEdgeEncountered++;
        printf("%d %d\n",u,v);
        j=Parent(u);
        k=Parent(v);
        if(j!=k){
            parent[j]=k;
            t[i][1]=u;
            t[i][2]=v;
            i++;
            mincost+=cost[u][v];
        }
    }
    return mincost;
}

int main(){

create();

int cost=kruskals();
printf("%d\n",cost);
for(int i=1;i<=n-1;i++){
    printf("%d %d\n",t[i][1],t[i][2]);
}


return 0;
}