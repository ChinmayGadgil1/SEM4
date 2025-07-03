# include<stdio.h>
# include<string.h>
#define MAX 100
char P[MAX];
char T[MAX];
int m;
int last(char x){
    for(int i=m-1;i>0;i--){
        if(P[i]==x)return i;
    }
    return 0; 
}

int min(int a,int b){
    if(a<=b) return a;
    else return b;
}

int BM(int n,int m){
    int i=m-1,j=m-1,count=0;
    do{
        count++;
        if(T[i]==P[j]){
            if(j==0) {
                printf("%d",count);
                return i;
            }
            i--;
            j--;
        }
        else{
            i=i+m-min(j,last(T[i])+1);
            j=m-1;
        }
    }while(i<n);
    return -1;
}

int main(){
    int n;
    scanf("%s",T);
    scanf("%s",P);
    n=strlen(T);
    m=strlen(P);
    int i=BM(n,m);
    if(i==-1){
        printf("Not found");
    }
    else{
        printf("Found at index %d",i);
    }
    return 0;
}