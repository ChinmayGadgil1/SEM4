#include <stdio.h>
#define MAX 20
int G[MAX][MAX];
int n, m,solFound=0;
int x[MAX] = {0};
void create()
{
    int max_edges, org, dest;
    printf("Enter number of vertices:");
    scanf("%d", &n);
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            G[i][j] = 0;
        }
    }
    printf("Enter edges:\n");
    for (int i = 0; i < max_edges; i++)
    {
        scanf("%d%d", &org, &dest);
        if (org == -1 && dest == -1)
            break;
        if (org < 1 || dest < 1 || org > n || dest > n)
        {
            printf("Invalid edge\n");
            i--;
        }
        G[org][dest] = 1;
        G[dest][org] = 1;
    }
}

void NextValue(int k)
{
    do
    {
        x[k] = (x[k] + 1) % (m + 1);
        if (x[k] == 0)
            return;
        int j;
        for( j=1;j<=n;j++){
            if(x[j]==x[k] && G[k][j]!=0){
                break;
            }
        }
        if(j==n+1){
            return;
        }
    } while (1);
}

void mcolor(int k){
    do
    {
        NextValue(k);
        if(x[k]==0) return;
        if(k==n) {
            for (int i = 1; i <=n; i++)
            {
                printf("%d ",x[i]);
            }
            solFound=1;
            printf("\n");
        }
        else{
            mcolor(k+1);
        }
    } while (1);
    
}

int findM(){
    int m=0;
    int tmp;
    for (int i = 1; i <=n; i++)
    {
        tmp=0;
        for (int j = 1; j <=n; j++)
        {
            if(G[i][j]==1){
                tmp++;
            }
        }
        if(tmp>m){
            m=tmp;
        }
        
    }
    return m;
}

int main()
{
    create();
    int deg=findM();
    for (m=0; m <=deg ; m++)
    {
        mcolor(1);
        if(solFound) break;
    }
    
    return 0;
}