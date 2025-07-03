#include <stdio.h>
#define MAX 20
#define inf 100000

int G[MAX][MAX];
int n;
int x[MAX]={0};

void create()
{
    int max_edges, org, dest;
    printf("Enter number of vertices:");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i <MAX; i++)
    {
        for (int j = 0; j <MAX; j++)
        {
            G[i][j]=0;
        }
    }
    for (int i = 1; i <=n; i++)
    {
        for (int j = 1; j <=n; j++)
        {
            scanf("%d",&G[i][j]);
        }
    }

}

void NextValue(int k){
    do
    {
        x[k]=(x[k]+1)%(n+1);
        if(x[k]==0) return;
        if(G[x[k-1]][x[k]]!=0){
            int j;
            for(j=1;j<=k-1;j++){
                if(x[j]==x[k]) break;
            }
            if(j==k){
                if((k<n) || (k==n && G[x[k]][x[1]]!=0)){
                    return;
                }
            }
        }
    } while (1);
    
}

void hamiltonian(int k)
{
    do
    {
        NextValue(k);
        if(x[k]==0) return;
        if (k == n){
            for(int i=1;i<=n;i++){
                printf("%d ",x[i]);
            }
            printf("\n");
        }
        else{
            hamiltonian(k + 1);
        }
    } while (1);
}

int main()
{
    create();
    x[1]=1;
    printf("\n");
    hamiltonian(2);
    return 0;
}