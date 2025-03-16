#include <stdio.h>
#include <limits.h>
#define inf INT_MAX
#define MAX 100 // Maximum size for arrays

// Function to select the vertex with minimum cost
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

// Function to implement the FGraph algorithm with 1-based indexing
void FGraph(int c[MAX][MAX], int k, int n, int p[MAX]) {
    int cost[MAX];
    int d[MAX] = {0};
    
    // Initialize cost array
    for (int i = 1; i <= n; i++) {
        cost[i] = inf;
    }
    cost[n] = 0; // Set the terminal vertex cost to 0
    
    // Dynamic programming approach - compute cost from end to start
    for (int j = n-1; j >= 1; j--) {
        int r = selectVertex(c, j, cost, n);
        if (r != -1) {
            cost[j] = c[j][r] + cost[r];
            d[j] = r;
        } else {
            cost[j] = inf;
            d[j] = j;
        }
        
        int stage = 0;
        if (j >= 10) stage = 4;
        else if (j >= 6) stage = 3;
        else if (j >= 2) stage = 2;
        else stage = 1;
        
        printf("Cost(%02d,%02d)=%02d  ", stage, j, cost[j]);
        printf("r(%02d,%02d)=%02d\n", stage, j, d[j]);
    }
    
    // Find minimum-cost path
    p[1] = 1;
    p[k] = n;
    
    // Reconstruct the path
    for (int j = 2; j <= k-1; j++) {
        p[j] = d[p[j-1]];
    }
    
    // Print the final path
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
    int bcost[MAX];
    int d[MAX];
    
    for (int i = 0; i <= n; i++) {
        bcost[i] = inf;
        d[i] = 0;
    }
    bcost[1] = 0; 

    for (int j = 2; j <= n; j++) {
        int stage = 0;
        if (j <= 4) stage = 1;
        else if (j <= 8) stage = 2;
        else if (j <= 12) stage = 3;
        else stage = 4;
        
        int r = selectVertexB(c, j, bcost, n);
        if (r > 0) {
            bcost[j] = c[r][j] + bcost[r];
            d[j] = r;
        } else {
            bcost[j] = inf;
            d[j] = 0;
        }
        
        printf("Cost(%02d,%02d)=%02d  ", stage, j, bcost[j]);
        printf("r(%02d,%02d)=%02d\n", stage, j, d[j]);
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

int main() {
    int n = 14;
    int k = 5;
    int p[MAX] = {0};
    
    int cost[MAX][MAX] = {0};
    
    // Initialize cost matrix with infinity
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cost[i][j] = inf;
        }
    }
    
    // Sample graph from the reference code
    int graph[15][15] = {
        {inf},
        {inf,inf,9,8,6,7,inf,inf,inf,inf,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,10,11,12,inf,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,15,inf,14,13,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,inf,10,11,12,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,8,9,inf,10,inf,inf,inf,inf,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,5,6,inf,7,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,8,9,7,inf,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,6,7,8,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,5,inf,8,6,inf},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,8},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,9},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,8},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,7},
        {inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},
    };
    
    // Copy graph to cost matrix
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            cost[i][j] = graph[i][j];
        }
    }
    
    printf("Forward Graph Algorithm:\n");
    FGraph(cost, k, n, p);
    
    printf("\nBackward Graph Algorithm:\n");
    Bgraph(cost, k, n, p);
    
    return 0;
}