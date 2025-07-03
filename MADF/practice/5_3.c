# include<stdio.h>
# include<string.h>
#define MAX 100
char P[MAX];
char T[MAX];
int failureFunction[MAX];

void Failure(int m){
    failureFunction[0]=0;
    int i=1,j=0;
    while(i<m){
        if(P[i]==P[j]){
            failureFunction[i]=j+1;
            i++;
            j++;
        }
        else if(j>0){
            j=failureFunction[j-1];
        }
        else{
            failureFunction[i]=0;
            i++;
        }
    }
}

int KMP(int n,int m){
    Failure(m);
    int count=0,i=0,j=0;
    while(i<n){
        while(j<m){
            count++;
            if(T[i]==P[j]){
                if(j==m-1){
                    printf("%d\n",count);
                    return i-m+1;
                }
                i++;
                j++;
            }
            else if(j>0){
                j=failureFunction[j-1];
            }
            else{
                i++;
            }
        }
    }
   return -1;
}

int main(){
    int n,m;
    scanf("%s",T);
    scanf("%s",P);
    n=strlen(T);
    m=strlen(P);
    int i=KMP(n,m);
    if(i==-1){
        printf("Not found");
    }
    else{
        printf("Found at index %d",i);
    }
    return 0;
}