# include<stdio.h>
#define MAX 100

int P[MAX];
int W[MAX];
double P_per_W[MAX];
double X[MAX];

void sort(double* arr, int n){
    for (int i = 0; i < n; i++)
    {
        int flag=0;
        for (int j = i; j < n-i; j++)
        {
            if(arr[j]<arr[j+1]){
                int tmp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=tmp;
                flag=1;
            }
        }
        if(flag==0){
            break;
        }
        
    }
    
}

void Knapsack(int m,int n){
    for (int i = 0; i < n; i++)
    {
        X[i]=0;
    }
    int u=m,i;
    for (i = 0; i < n; i++)
    {
        if(P_per_W[i]>u) break;
        X[i]=1.0;
        u-=W[i];
    }
    if (i!=n)
    {
        X[i]=u/W[i];
    }
    
}

int main(){

// int m,n;
// printf("Enter knapsack capacity: ");
// scanf("%d",&m);
// printf("Enter number of elements: ");
// scanf("%d",&n);

// printf("Enter prices and weights:\n");
// printf(" P W\n");
// for (int i = 0; i < n; i++)
// {
//     scanf("%d%d",&P[i],&W[i]);
// }
int m=30,n=10;
int x[]={5,5,4,2,5,6,3,4,8,2};
int y[]={23,13,26,34,11,26,31,19,19,26};

for (int i = 0; i < n; i++)
{
    W[i]=x[i];
    P[i]=y[i];
}


for (int i = 0; i < n; i++)
{
    P_per_W[i]=(P[i])/(float)W[i];
}

sort(P_per_W,n);

for (int i = 0; i < n; i++)
{
    printf("%f ",P_per_W[i]);
}

printf("\n");
Knapsack(m,n);

int max_prof=0;
int w=0;
for(int i=0;i<n;i++){
    printf("%.2f ",X[i]);
    max_prof+=X[i]*P[i];
    w+=(X[i]*W[i]);
}
printf("%f    %f\n",w,max_prof);


return 0;
}