# include<stdio.h>
#define MAX 100
int arr[MAX];
int n;
int partition(int low,int high){
    int pivot=arr[low];
    int i=low+1;
    int j=high;
    while(i<=j){
        while(arr[i]<=pivot)
            i++;
        while(arr[j]>pivot)
            j--;
        if(i<j){
            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }
    int temp=arr[low];
    arr[low]=arr[j];
    arr[j]=temp;
    return j;
}

void quicksort(int low,int high){
    if(low<high){
        int pivloc=partition(low,high);
        quicksort(low,pivloc-1);
        quicksort(pivloc+1,high);
    }
}

void display(){
    for (int i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");   
}

int main(){

printf("Enter the number of elements: ");
scanf("%d",&n);

for (int  i = 0; i < n; i++)
{
    scanf("%d",&arr[i]);
}
quicksort(0,n-1);

display();


return 0;
}