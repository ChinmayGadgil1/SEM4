#include <stdio.h>
#define MAX 20
#include<stdbool.h>
#include<stdlib.h>
int x[MAX]={0};

int solcount=0;
void write(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j == x[i])
            {
                printf("Q%02d ", i);
            }
            else
            {
                printf("--- ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

bool Place(int k,int i){
    for(int j=1;j<=k-1;j++){
        if(x[j]==i || abs(x[j]-i)==abs(j-k)){
            return false;
        }
    }
    return true;
}

void NQueens(int k, int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (Place(k, i))
        {
            x[k] = i;
            if (k == n)
            {
                if(solcount==0){
                    write(n);
                }
                solcount++;
            }else{
            NQueens(k+1,n);
        }
        }
    }
}

int main()
{

    for(int i=4;i<=12;i++){
        NQueens(1,i);
        printf("solcount for %d queens=%d\n\n",i,solcount);
        solcount=0;
    }

    return 0;
}