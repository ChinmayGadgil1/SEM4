# include<stdio.h>
#define MAX 100
int w[MAX][MAX];
int c[MAX][MAX];
int r[MAX][MAX];  


int Find(int c[MAX][MAX],int r[MAX][MAX],int i,int j){
    int l;
    int min=9999;
    for (int m = r[i][j-1]; m <=r[i+1][j]; m++)
    {
        if(c[i][m-1]+c[m][j]<min){
            min=c[i][m-1]+c[m][j];
            l=m;
        }
    }
    return l;
}

void OBST(int p[],int q[],int n){
    for (int i = 0; i <= n-1; i++)
    {   
        w[i][i]=q[i];
        c[i][i]=0;
        r[i][i]=0;
        w[i][i+1]=q[i]+q[i+1]+p[i+1];
        r[i][i+1]=i+1;
        c[i][i+1]=q[i]+q[i+1]+p[i+1];
    }w[n][n]=q[n]; r[n][n]=0;c[n][n]=0;

    for (int i = 0; i <=n; i++)
    {
        printf("w[%d][%d]=%d ",i,i,w[i][i]);
    }
    printf("\n");
    for (int i = 0; i <=n; i++)
    {
        printf("c[%d][%d]=%d ",i,i,c[i][i]);
    }
    printf("\n");
    for (int i = 0; i <=n; i++)
    {
        printf("r[%d][%d]=%d ",i,i,r[i][i]);
    }
    printf("\n");


    for (int m = 2; m <=n; m++)
    {
        for (int i = 0; i <= n-m; i++)
        {
            int j=i+m;
            w[i][j]=w[i][j-1]+p[j]+q[j];
            int k=Find(c,r,i,j);
            c[i][j]=w[i][j]+c[i][k-1]+c[k][j];
            r[i][j]=k;
        }
    }
    printf("w[%d][%d]=%d\n",0,n,w[0][n]);
    printf("c[%d][%d]=%d\n",0,n,c[0][n]);
    printf("r[%d][%d]=%d\n",0,n,r[0][n]);
}

int main(){

    int n;
    printf("Enter the number of keys\n");
    scanf("%d",&n);
    int p[n+1],q[n+1];
    printf("Enter the probability of successful search\n");
    for (int i = 1; i <= n; i++)
    {
        scanf("%d",&p[i]);
    }
    printf("Enter the probability of unsuccessful search\n");
    for (int i = 0; i <= n; i++)
    {
        scanf("%d",&q[i]);
    }
    OBST(p,q,n);

return 0;
}