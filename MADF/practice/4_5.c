#include <stdio.h>
#define MAX 10
int x[MAX] = {0};
int n, m;
int w[MAX] = {0};

void sumOfSubsets(int s,int k,int r){
    x[k]=1;
    if(s+w[k]==m){
        for(int i=1;i<=k;i++){
                printf("%d ",x[i]);
        }
        printf("\n");
    }
    else if(s+w[k]+w[k+1]<=m){
        sumOfSubsets(s+w[k],k+1,r-w[k]);
    }

    if((s+r-w[k]>=m) && s+w[k+1]<=m){
        x[k]=0;
        sumOfSubsets(s,k+1,r-w[k]);
    }
}

int main()
{
    int r=0, s=0;
    printf("Enter the number of elements in set: ");
    scanf("%d", &n);
    printf("Enter m: ");
    scanf("%d", &m);
    printf("Enter %d elements: ", n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &w[i]);
        r+=w[i];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n - i; j++)
        {
            if (w[j] > w[j + 1])
            {
                int temp = w[j];
                w[j] = w[j + 1];
                w[j + 1] = temp;
            }
        }
    }

    sumOfSubsets(s,1,r);


    return 0;
}