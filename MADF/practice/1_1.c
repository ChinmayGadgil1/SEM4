#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

int BinarySearch(char** arr,int low,int high,char* target){
    if(low<=high){
        int mid=(low+high)/2;
        if(strcmp(arr[mid],target)==0){
            return mid;
        }
        else if(strcmp(arr[mid],target)>0){
            return BinarySearch(arr,low,mid-1,target);
        }
        else{
            return BinarySearch(arr,mid+1,high,target);
        }
    }
        return 0;
}

int main(){
    char ** arr;
    int n;
    char target[100];
    label:
    printf("Enter size of set:");
    scanf("%d",&n);
    if(n<1){
        goto label;
    }
    arr=(char**)malloc((n+1)*sizeof(char*));
    if(arr==NULL){
        printf("Failed allocation");
        exit(1);
    }
    printf("Enter n strings:\n");
    for (int i = 1; i <=n; i++)
    {
        arr[i]=(char*)malloc(50*sizeof(char));
        scanf("%s",arr[i]);
    }
    printf("Enter target:");
    scanf("%s",target)
    ;arr[0]=NULL;
    int index=BinarySearch(arr,1,n,target);
    if(index!=0){
        printf("Found at index %d",index);
    }
    else{
        printf("Not found");
    }
    for (int i = 1; i <=n; i++)
    {
        free(arr[i]);
    }
    free(arr);
}