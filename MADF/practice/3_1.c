# include<stdio.h>
#include<stdlib.h>
#define MAX 20
#define inf 100000
int cost[MAX][MAX];
int p[MAX][MAX];
int A[MAX][MAX];
int n;

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
        for (int j = 0; j < MAX; j++)
        {
            p[i][j]=0;
            A[i][j]=inf;
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

void AllPair(){
    for (int i = 1; i <=n; i++)
    {
        for(int j=1;j<=n;j++){
            A[i][j]=cost[i][j];
            p[i][j]=i;
        }
    }

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(A[i][j]>A[i][k]+A[k][j]){
                    p[i][j]=p[k][j];
                    A[i][j]=A[i][k]+A[k][j];
                }
            }
        }
    }
}

void path(int i,int j){
    if(i==j){
        printf("%d",i);
        return;
    }
    path(i,p[i][j]);
    printf("->%d",j);
}

int main(){

create();
AllPair();

for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        printf("%d ",A[i][j]);
    }
    printf("\n");
}

for(int i=1;i<=n;i++){
    printf("Path from %d\n",i);
    for(int j=1;j<=n;j++){
        if(i==j)continue;
        path(i,j);
        printf("\n");
    }
    printf("\n");
}



return 0;
}