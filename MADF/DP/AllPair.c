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
    int cost[MAX][MAX] = {inf};
    int graph[15][15] = {
        {inf},
        {inf,inf,9,8,6,7,inf,inf,inf,inf,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,10,11,12,inf,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,15,inf,14,13,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,inf,10,11,12,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,8,9,inf,10,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,5,6,inf,7,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,8,9,7,inf,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,6,7,8,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,5,inf,8,6,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,8},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,9},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,8},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,7},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},
    };
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            cost[i][j] = graph[i][j];
        }
    }
    int n=14;
    int A[MAX][MAX];
    AllPairShortest(cost,A,n);
    display(A,n);
return 0;
}