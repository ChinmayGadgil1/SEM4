# include<stdio.h>
#define MAX 100

int arr[MAX], n;


void MinMax(int i,int j, int *min, int *max){
    if(i==j){
        *max=*min=arr[i];
    }
    else if(i==j-1){
        if(arr[i]>arr[j]){
            *max=arr[i];
            *min=arr[j];
        }
        else{
            *max=arr[j];
            *min=arr[i];
        }
    }
    else{
        int mid=(i+j)/2;
        int min1, max1;
        MinMax(i,mid,min,max);
        MinMax(mid+1,j,&min1,&max1);
        if(*min>min1){
            *min=min1;
        }
        if(*max<max1){
            *max=max1;
        }
    }
}

int main(){

printf("Enter the number of elements: ");
scanf("%d",&n);

for (int  i = 0; i < n; i++)
{
    scanf("%d",&arr[i]);
}

int min, max;
MinMax(0,n-1,&min,&max);
printf("Minimum: %d\nMaximum: %d\n",min,max);



return 0;
}