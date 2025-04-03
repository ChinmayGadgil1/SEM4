#include <stdio.h> 
#include <stdbool.h> 
#include <limits.h>
#include<sys/time.h>


long long current_time_us(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

#define N 8 
#define INF 99999 

// Initialize all elements of a matrix with INF 
void fillInf(int a[][N], int n) { 
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] = INF;
            
    // Set diagonal to 0 for self-loops
    for (int i = 1; i <= n; i++)
        a[i][i] = 0;
} 

// Read the input matrix 
void getMatrix(int a[][N], int n) { 
    int w, x, y;
    printf("Enter edge information as 'x y weight' (-1 -1 -1 to exit):\n");
    for (int i = 0; i < n * (n - 1); i++) {
        scanf("%d", &x);
        scanf("%d", &y);
        scanf("%d", &w);
        if (x == -1 && y == -1) 
            return;
            
        if (x < 1 || x > n || y < 1 || y > n) {
            printf("Invalid vertices! Please enter values between 1 and %d\n", n);
            i--;
            continue;
        }
        
        a[x][y] = w;
    } 
} 

// Show a 1D matrix (distance array)
void showMatrix(int a[N], bool changed[N], int n) { 
    for (int i = 1; i <= n; i++) {
        if (a[i] == INF) 
            printf("∞\t");
        else if (changed[i]) 
            printf("[%d]\t", a[i]); // Changed formatting for consistency
        else 
            printf("%d\t", a[i]);
    } 
    printf("\n");
} 

// Check if there's an incoming edge to a vertex 
int hasIncoming(int u, int a[][N], int v) { 
    for (int i = 1; i <= v; i++)
        if (a[i][u] != INF && i != u) 
            return 1;
    return 0;
} 

// Show a 2D matrix 
void show2DMatrix(int a[][N], bool changed[][N], int n) { 
    printf("    ");
    for (int j = 1; j <= n; j++) {
        printf("[%d] ", j);
    }
    printf("\n");
    
    for (int i = 1; i <= n; i++) { 
        printf("[%d] ", i);
        for (int j = 1; j <= n; j++) { 
            if (a[i][j] == INF) 
                printf("∞   ");
            else if (changed[i][j]) 
                printf("[%d] ", a[i][j]); 
            else 
                printf("%2d  ", a[i][j]); 
        } 
        printf("\n");
    } 
}

// Get path from source to destination
void getPath(int src, int dest, int pred[N], char* pathStr) {
    if (dest == src) {
        sprintf(pathStr, "%d", src);
        return;
    }
    
    char tempPath[100];
    getPath(src, pred[dest], pred, tempPath);
    sprintf(pathStr, "%s → %d", tempPath, dest);
}

// Bellman-Ford algorithm 
void bellmanFord(int src, int cost[][N], int v) { 
    int dist1[N], dist2[N]; // Arrays to store distances
    int pred[N]; // Array to store predecessors
    bool changed[N]; // Array to track changes in dist1
    
    // Initialize distances and predecessors 
    for (int i = 1; i <= v; i++) {
        dist1[i] = dist2[i] = cost[src][i];
        pred[i] = src;
        changed[i] = false;
    } 
    dist1[src] = dist2[src] = 0; // Distance to source is 0
    
    // Print header for vertices
    printf("\nVertex: ");
    for (int i = 1; i <= v; i++) {
        printf("[%d]\t", i);
    }
    printf("\n");
    
    printf("k = 1: ");
    showMatrix(dist1, changed, v);
    
    printf("Paths updated: ");
    for (int j = 1; j <= v; j++) {
        if (j != src && dist1[j] != INF) {
            printf("(%d→%d)\t", pred[j], j);
        }
    } 
    printf("\n\n");
    
    // Relax edges repeatedly 
    for (int k = 2; k <= v - 1; k++) {
        bool changed_u[N] = {false}; // Array to track changes for each vertex in this iteration
        
        for (int u = 1; u <= v; u++) {
            if (u != src && hasIncoming(u, cost, v) == 1) { 
                dist2[u] = dist1[u];
                for (int i = 1; i <= v; i++) {
                    if (cost[i][u] != INF) { 
                        if (dist1[i] != INF && dist2[u] > dist1[i] + cost[i][u]) { 
                            dist2[u] = dist1[i] + cost[i][u];
                            pred[u] = i;
                            changed[u] = true; // Mark that distance of vertex u has changed
                            changed_u[u] = true; // Mark that distance of vertex u has changed in this iteration
                        } 
                    } 
                } 
            } 
        } 
        
        printf("k = %d: ", k);
        showMatrix(dist2, changed, v);
        
        // Print paths updated in this iteration
        printf("Paths updated: ");
        bool updatesFound = false;
        for (int j = 1; j <= v; j++) {
            if (changed_u[j]) { 
                printf("(%d→%d)\t", pred[j], j);
                updatesFound = true;
            } 
        } 
        if (!updatesFound) {
            printf("None");
        }
        printf("\n\n");
        
        // Swap arrays and reset changed array 
        for (int i = 1; i <= v; i++) {
            dist1[i] = dist2[i];
            changed[i] = false;
        } 
    } 
    
    // Check for negative cycles 
    bool hasCycle = false;
    for (int u = 1; u <= v; u++) {
        if (u != src && hasIncoming(u, cost, v) == 1) { 
            for (int i = 1; i <= v; i++) {
                if (cost[i][u] != INF && dist1[i] != INF) { 
                    if (dist1[u] > dist1[i] + cost[i][u]) { 
                        hasCycle = true;
                        printf("Negative cycle detected: %d → %d\n", i, u);
                        break;
                    } 
                } 
            } 
        }
        if (hasCycle) break;
    } 
    
    if (!hasCycle) {
        printf("No negative cycle detected.\n");
    }
    
    // Print paths in a table 
    printf("\nShortest paths from source %d:\n", src);
    printf("+------+------+--------+------------------------+\n");
    printf("| Src  | Dest | Length | Path                   |\n");
    printf("+------+------+--------+------------------------+\n");
    
    for (int i = 1; i <= v; i++) {
        if (i != src) {
            char pathStr[100] = "";
            if (dist1[i] == INF) {
                sprintf(pathStr, "No path");
                printf("| %-4d | %-4d | ∞      | %-22s |\n", src, i, pathStr);
            } else {
                getPath(src, i, pred, pathStr);
                printf("| %-4d | %-4d | %-6d | %s \n", src, i, dist1[i], pathStr);
            }
        }
    }
    printf("+------+------+--------+------------------------+\n"); 
} 

int main() { 
    int n, graph[N][N], src;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    
    if (n > N-1) {
        printf("Number of vertices cannot exceed %d\n", N-1);
        return 1;
    }
    
    fillInf(graph, n);
    getMatrix(graph, n);
    
    printf("Enter the source vertex: ");
    scanf("%d", &src);
    
    if (src < 1 || src > n) {
        printf("Invalid source vertex! Must be between 1 and %d\n", n);
        return 1;
    }
    
    printf("\nAdjacency matrix:\n");
    bool dummy[N][N] = {false};
    show2DMatrix(graph, dummy, n);
    long long start=current_time_us();
    bellmanFord(src, graph, n);
    long long end=current_time_us();
    printf("\nTime taken: %lldμs\n", end - start);
    return 0;
} 




