# include<stdio.h>
#include<stdlib.h>
#define MAX 20
#define inf 100000

int cost[MAX][MAX];
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



int main(){



return 0;
}