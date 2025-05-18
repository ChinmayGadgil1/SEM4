#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int sort(int *arr, int n,int *B){
    for(int i=0;i<n;i++){
        B[i]=-1;
    }
    for(int i=0;i<n;i++)
    {
        int j = rand() % n;
        if(B[j]!=-1){
            return 0;
        }
        B[j]=arr[i];
    }
    for(int i=0;i<n-1;i++){
        if(B[i]>B[i+1]){
            return 0;
        }
    }

    return 1;
}

int main(){
    int n;
    int *arr,*B;
    printf("Enter the number of elements: ");
    scanf("%d",&n);
    arr=(int*)malloc(n*sizeof(int));
    B=(int*)malloc(n*sizeof(int));  
    printf("Enter the elements: ");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int result;
    do
    {
        result=sort(arr,n,B);
        for(int i=0;i<n;i++){
            printf("%2d ",B[i]);
        }
        printf("\n");
    } while (!result);

    free(arr);
    free(B);
return 0;
}   