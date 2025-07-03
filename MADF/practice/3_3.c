# include<stdio.h>
# define MAX 100
int w[MAX][MAX]={0};
int c[MAX][MAX]={0};
int r[MAX][MAX]={0};
char *a[5][MAX]={0};
int p[MAX]={0};
int q[MAX]={0};
int n;

int Find(int i,int j){
    int l,min=99999;
    for(int m=r[i][j-1];m<=r[i+1][j];m++){
        if(c[i][m-1]+c[m][j]<min){
            min=c[i][m-1]+c[m][j];
            l=m;
        }
    }
    return l;
}

void OBST(){
    for (int i = 0; i <=n-1; i++)
    {
        w[i][i]=q[i];
        c[i][i]=0;
        r[i][i]=0;

        w[i][i+1]=q[i]+p[i+1]+q[i+1];
        c[i][i+1]=q[i]+p[i+1]+q[i+1];
        r[i][i+1]=i+1;
    }
    w[n][n]=q[n];
    c[n][n]=0;
    r[n][n]=0;
    for(int m=2;m<=n;m++){
        for(int i=0;i<=n-m;i++){
            int j=m+i;
            int k=Find(i,j);
            w[i][j]=w[i][j-1]+p[j]+q[j];
            c[i][j]=c[i][k-1]+c[k][j]+w[i][j];
            r[i][j]=k;
        }
    }
}

int main(){
scanf("%d",&n);
for (int i = 1; i <= n; i++)
{
    scanf("%s",a[i]);
}
for(int i=1;i<=n;i++){
    scanf("%d",&p[i]);
}

for (int i = 0; i <=n; i++)
{
    scanf("%d",&q[i]);
}

OBST();


printf("%d %d %d",w[0][n],c[0][n],r[0][n]);



return 0;
}