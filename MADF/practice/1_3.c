# include<stdio.h>
int A[3][3],B[3][3],C[3][3];

void starssens(){
    int p=(A[1][1]+A[2][2])*(B[1][1]+B[2][2]);
    int q=(A[2][1]+A[2][2])*B[1][1];
    int r=(A[1][1])*(B[1][2]-B[2][2]);
    int s=A[2][2]*(B[2][1]-B[1][1]);
    int t=(A[1][1]+A[1][2])*B[2][2];
    int u=(A[2][1]-A[1][1])*(B[1][1]+B[1][2]);
    int v=(A[1][2]-A[2][2])*(B[2][1]+B[2][2]);

    C[1][1]=p+s-t+v;
    C[1][2]=r+t;
    C[2][1]=q+s;
    C[2][2]=p+r-q+u;

}



int main(){

for(int i=1;i<=2;i++){
    for(int j=1;j<=2;j++){
        scanf("%d",&A[i][j]);
    }
}

for(int i=1;i<=2;i++){
    for(int j=1;j<=2;j++){
        scanf("%d",&B[i][j]);
    }
}

starssens();

for(int i=1;i<=2;i++){
    for(int j=1;j<=2;j++){
        printf("%d ",C[i][j]);       
    }
    printf("\n");
}

return 0;
}   