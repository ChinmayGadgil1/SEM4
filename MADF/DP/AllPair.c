# include<stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define inf 10000
#define MAX 100

int min(int a,int b){
    if(a<b)
        return a;
    else return b;
}

void AllPairShortest(int cost[MAX][MAX],int A[MAX][MAX],int n){
    for (int i = 1; i <=n; i++)
    {
        for (int j = 1; j <=n; j++)
        {
            A[i][j]=cost[i][j];
        }
        
    }
    for (int k = 1; k <=n; k++)
    {
        for (int i = 1; i  <=n; i++)
        {
            for (int j = 1; j <=n; j++)
            {
                A[i][j]=min(A[i][j],A[i][k]+A[k][j]);
            }
            
        }
        
    }
    
}

void display(int A[MAX][MAX],int n){
    
    printf("\n");
    for (int i = 1; i <=n; i++)
    {
        for (int j = 1; j <=n; j++)
        {
            if(A[i][j]==inf){
                printf("inf ");
                continue;
            }
            printf("%3d ",A[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int n=14;
    int A[MAX][MAX];
    AllPairShortest(cost,A,n);
    display(A,n);
return 0;
}