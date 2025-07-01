#include<stdio.h>
#include<stdlib.h>
#define MAX 20
#define inf 100000
int n;
int cost[MAX][MAX];
int t[MAX][3];
int near[MAX];

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
    }
    
}

void select(int* k,int* l){
    int min_org=1,min_dest=2;
    for (int i = 1; i <=n; i++)
    {
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            if(cost[i][j]<cost[min_org][min_dest]){
                min_org=i;
                min_dest=j;
            }
        }
    }
    *k=min_org;
    *l=min_dest;
}

int choose(){
    int minindex,mincost=inf;
    for(int i=1;i<=n;i++){
        if(near[i]!=0 && cost[i][near[i]]<mincost){
            minindex=i;
            mincost=cost[i][near[i]];
        }
    }
    return minindex;
}

int prims(){
    int k,l,mincost=0,j;
    select(&k,&l);
    for(int i=1;i<=n;i++){
        if(cost[l][i]<cost[k][i]){
            near[i]=l;
        }
        else{
            near[i]=k;
        }
    }
    t[1][1]=k;
    t[1][2]=l;
    mincost+=cost[k][l];
    near[k]=near[l]=0;
    for(int i=2;i<=n-1;i++){
        int j=choose();
        mincost+=cost[j][near[j]];
        t[i][1]=j;
        t[i][2]=near[j];
        near[j]=0;
        for(int k=1;k<=n;k++){
            if(cost[j][k]<cost[k][near[k]] && near[k]!=0){
                near[k]=j;
            }
        }
    }
    return mincost;
}


int main(){
create();

int cost=prims();
printf("%d\n",cost);
for(int i=1;i<=n-1;i++){
    printf("%d %d\n",t[i][1],t[i][2]);
}


return 0;
}