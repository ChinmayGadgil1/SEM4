#include <stdio.h>
#include <limits.h>
#include<windows.h>

long long current_time_us(){
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (counter.QuadPart * 1000000) / freq.QuadPart;
}

#define inf INT_MAX
#define MAX 100 
int n,k;

void createGraph(int G[MAX][MAX]){
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of stages: ");
    scanf("%d", &k);
    int max_edges = n * (n - 1) / 2;
    int origin, destin,weight;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            if(i == j && (i!=0 && j!=0)) G[i][j] = 0;
            else
            G[i][j] = inf;
        }
    }

    printf("(-1,-1) to quit\n");
    printf("Enter edges and weight: \n");
    for (int i = 1; i <= max_edges; i++)
    {
        scanf("%d%d%d", &origin, &destin,&weight);
        if ((origin == -1) && (destin == -1))
        {
            break;
        }
        if (origin > n || destin > n || origin < 1 || destin < 1)
        {
            printf("Invalid edge\n");
            i--;
        }
        else
        {
            G[origin][destin] = weight;
        }
    }


}

int selectVertex(int c[MAX][MAX], int j, int cost[MAX], int n) {
    int min_cost = inf;
    int min_vertex = -1;
    
    for(int r = j+1; r <= n; r++) {
        if(c[j][r] != inf && cost[r] != inf) {
            int current_cost = c[j][r] + cost[r];
            if(current_cost < min_cost) {
                min_cost = current_cost;
                min_vertex = r;
            }
        }
    }
    return min_vertex;
}


void FGraph(int c[MAX][MAX], int k, int n, int p[MAX]) {
    int cost[MAX],stage[n];
    int d[MAX] = {0};
    stage[1]=1; stage[n]=k;
   
    for (int i = 1; i <= n; i++) {
        cost[i] = inf;
    }
    cost[n] = 0; 
    
    for (int j = n-1; j >= 1; j--) {
        int r = selectVertex(c, j, cost, n);
        if (r != -1) {
            cost[j] = c[j][r] + cost[r];
            d[j] = r;
        } else {
            cost[j] = inf;
            d[j] = j;
        }
        
        stage[j]=stage[r]-1;        
        
        printf("Cost(%02d,%02d)=%02d  ", stage[j], j, cost[j]);
        printf("r(%02d,%02d)=%02d\n", stage[j], j, d[j]);
    }
    
    p[1] = 1;
    p[k] = n;
    
    for (int j = 2; j <= k-1; j++) {
        p[j] = d[p[j-1]];
    }
 
    printf("Shortest path is: ");
    printf("%d", p[1]);
    for (int i = 2; i <= k; i++) {
        printf("->%d", p[i]);
    }
    printf("\nMincost=%d\n", cost[1]);
}
int selectVertexB(int c[MAX][MAX], int j, int bcost[MAX], int n) {
    int min_cost = inf;
    int min_vertex = 0;

    for (int r = 1; r < j; r++) {
        if (c[r][j] != inf && bcost[r] != inf) {
            int total_cost = c[r][j] + bcost[r];
            if (total_cost < min_cost) {
                min_cost = total_cost;
                min_vertex = r;
            }
        }
    }
    return min_vertex;
}

void Bgraph(int c[MAX][MAX], int k, int n, int p[MAX]) {
    int bcost[MAX],stage[n];
    int d[MAX];
    stage[1]=1;stage[n]=k;
    for (int i = 0; i <= n; i++) {
        bcost[i] = inf;
        d[i] = 0;
    }
    bcost[1] = 0; 

    for (int j = 2; j <= n; j++) {        
        int r = selectVertexB(c, j, bcost, n);
        if (r > 0) {
            bcost[j] = c[r][j] + bcost[r];
            d[j] = r;
        } else {
            bcost[j] = inf;
            d[j] = 0;
        }
        stage[j]=stage[r]+1;   
        printf("Cost(%02d,%02d)=%02d  ", stage[j], j, bcost[j]);
        printf("r(%02d,%02d)=%02d\n", stage[j], j, d[j]);
    }
    
    p[1] = 1;      
    p[k] = n;      
    
    for (int j = k - 1; j >= 2; j--) {
        p[j] = d[p[j + 1]];
    }
    
    printf("Shortest path is: ");
    printf("%d", p[1]);
    for (int i = 2; i <= k; i++) {
        printf("->%d", p[i]);
    }
    printf("\nMincost=%d\n", bcost[n]);
}

void menu(){
    printf("\nMenu\n");
    printf("1. Forward Graph Algorithm\n");
    printf("2. Backward Graph Algorithm\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    int p[MAX] = {0};
    
  
    int cost[MAX][MAX] = {0};
    int G[MAX][MAX] = {0};
    createGraph(G);
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cost[i][j] = inf;
        }
    }
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            cost[i][j] = G[i][j];
        }
    }
    
    do
    {
        menu();
        scanf("%d",&choice);
        if (choice==1)
        {
            
            printf("Forward Graph Algorithm:\n");
            long long start = current_time_us();
            FGraph(cost, k, n, p);
            long long end = current_time_us();
            printf("Time taken for forward graph: %lldμs\n", end - start);
        }
        else if(choice==2){
            long long start = current_time_us();
            printf("\nBackward Graph Algorithm:\n");
            Bgraph(cost, k, n, p);
            long long end=current_time_us();
            printf("Time taken for backward graph: %lldμs\n", end - start);
        }
        else if(choice==3){
            continue;
        }
        else{
            printf("Invalid Input");
        }
    } while (choice!=3);
    

    
    
    return 0;
}

