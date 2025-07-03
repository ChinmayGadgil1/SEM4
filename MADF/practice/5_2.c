#include <stdio.h>
#include <string.h>
#define MAX 20
char X[MAX];
char Y[MAX];
char L[MAX][MAX]={0};
char subs[MAX];
char tracer[MAX][MAX];

#define UP_ARROW '^'
#define LEFT_ARROW '<'
#define DIAGONAL_ARROW '\\'

int max(int a,int b){
    if(a>b) return a;
    else return b;
}

void LCS(int n,int m){
    for(int i=0;i<=n;i++){
        L[i][0]=0;
    }
    for(int i=0;i<=m;i++){
        L[0][i]=0;
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(X[i-1]==Y[j-1]){
                L[i][j]=L[i-1][j-1]+1;
            }
            else{
                L[i][j]=max(L[i-1][j],L[i][j-1]);
            }
        }
    }

}

void traverse(int n,int m){
    int i=n,j=m;
    int c=L[n][m];
    while(c>0){
        if(X[i-1]==Y[j-1]){
            subs[c]=X[i-1];
            tracer[i][j]=DIAGONAL_ARROW;
            c--;
            i--;
            j--;
        }else{
            if(L[i-1][j]>L[i][j-1]){
                tracer[i][j]=UP_ARROW;
                i--;
                

            }else{
                tracer[i][j]=LEFT_ARROW;
                j--;
            }
        }
    }
}

int main()
{
    printf("Enter X: ");
    scanf("%s", X);
    printf("Enter Y: ");
    scanf("%s", Y);

    int n = strlen(X);
    int m = strlen(Y);

    LCS(n,m);
    printf("%d\n",L[n][m]);
    traverse(n,m);
    for(int i=1;i<=L[n][m];i++){
        printf("%c",subs[i]);
    }

    printf("\n");
    return 0;
}