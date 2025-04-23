#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>

#define N 100
#define INF INT_MAX

// Function prototypes
void fillInf(int graph[][N], int n);
void getMatrix(int graph[][N], int n);
void show2DMatrix(int graph[][N], int n);
void bellmanFord(int src, int graph[][N], int n);
void printPath(int parent[], int j);
long long current_time_us();

// Fill adjacency matrix with infinity
void fillInf(int graph[][N], int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }
}

// Get adjacency matrix from user
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

// Display adjacency matrix
void show2DMatrix(int graph[][N], int n) {
    printf("   ");
    for (int i = 1; i <= n; i++)
        printf("%4d", i);
    printf("\n");
    
    for (int i = 1; i <= n; i++) {
        printf("%2d ", i);
        for (int j = 1; j <= n; j++) {
            if (graph[i][j] == INF)
                printf("   ∞");
            else
                printf("%4d", graph[i][j]);
        }
        printf("\n");
    }
}

// Print dist array in a formatted table
void printDistTable(int dist[][N], int n, int iterations) {
    // Print header for dist table
    printf("\n%5s", "k");
    for (int i = 1; i <= n; i++) {
        printf("%4d", i);
    }
    printf("\n");
    
    // Print horizontal line
    for (int i = 0; i <= n; i++) {
        printf("----");
    }
    printf("\n");
    
    // Print each iteration
    for (int k = 1; k <= iterations; k++) {
        printf("%4d |", k);
        for (int i = 1; i <= n; i++) {
            if (dist[k][i] == INF)
                printf("  ∞ ");
            else
                printf("%3d ", dist[k][i]);
        }
        printf("\n");
    }
}

// Recursive function to print path
void printPath(int parent[], int j) {
    // Base Case: If j is source or path doesn't exist
    if (parent[j] == -1)
        return;
    
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// Bellman-Ford algorithm implementation with formatted output and path tracking
void bellmanFord(int src, int graph[][N], int n) {
    int dist[N][N]; // dist[k][v] = distance to vertex v after k iterations
    int parent[N];  // To store the predecessor/parent of each vertex
    
    // Initialize parent array
    for (int i = 1; i <= n; i++) {
        parent[i] = -1;
    }
    
    // Initialize dist for k=1
    for (int i = 1; i <= n; i++) {
        if (i == src)
            dist[1][i] = 0;
        else {
            dist[1][i] = graph[src][i];
            if (graph[src][i] != INF)
                parent[i] = src;
        }
    }
    
    // Relax all edges n-1 times
    for (int k = 2; k <= n; k++) {
        // Copy previous distances
        for (int i = 1; i <= n; i++) {
            dist[k][i] = dist[k-1][i];
        }
        
        for (int u = 1; u <= n; u++) {
            if (u != src) {
                // Check if u has at least one incoming edge
                bool has_incoming = false;
                for (int i = 1; i <= n; i++) {
                    if (graph[i][u] != INF) {
                        has_incoming = true;
                        break;
                    }
                }
                
                if (has_incoming) {
                    // Check each incoming edge to u
                    for (int i = 1; i <= n; i++) {
                        if (graph[i][u] != INF && dist[k-1][i] != INF) {
                            if (dist[k][u] > dist[k-1][i] + graph[i][u]) {
                                dist[k][u] = dist[k-1][i] + graph[i][u];
                                parent[u] = i; // Update parent
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Check for negative weight cycles
    bool has_negative_cycle = false;
    for (int u = 1; u <= n; u++) {
        if (u != src) {
            for (int i = 1; i <= n; i++) {
                if (graph[i][u] != INF && dist[n][i] != INF && dist[n][u] > dist[n][i] + graph[i][u]) {
                    has_negative_cycle = true;
                    break;
                }
            }
            if (has_negative_cycle) break;
        }
    }
    
    // Print the results in tabular format
    printf("\ndist[1..%d] after each iteration:\n", n);
    printDistTable(dist, n, n);
    
    if (has_negative_cycle) {
        printf("\nWARNING: Graph contains negative weight cycle!\n");
    } else {
        printf("\nFinal shortest distances and paths from source vertex %d:\n", src);
        for (int i = 1; i <= n; i++) {
            if (i != src) {
                if (dist[n][i] == INF) {
                    printf("Vertex %d: INF (unreachable)\n", i);
                } else {
                    printf("Vertex %d: Distance = %d, Path: %d", i, dist[n][i], src);
                    printPath(parent, i);
                    printf("\n");
                }
            }
        }
    }
}

// Get current time in microseconds
long long current_time_us() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

int main() {
    int n, graph[N][N], src, choice;
    bool graphCreated = false;
    
    while(1) {
        printf("\n1. Create Graph\n");
        printf("2. Find Shortest Paths (Bellman-Ford)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter the number of vertices: ");
                scanf("%d", &n);
                if (n > N-1) {
                    printf("Number of vertices cannot exceed %d\n", N-1);
                    break;
                }
                fillInf(graph, n);
                getMatrix(graph, n);
                printf("\nAdjacency matrix:\n");
                show2DMatrix(graph, n);
                graphCreated = true;
                break;
                
            case 2:
                if (!graphCreated) {
                    printf("Please create a graph first!\n");
                    break;
                }
                printf("Enter the source vertex: ");
                scanf("%d", &src);
                if (src < 1 || src > n) {
                    printf("Invalid source vertex! Must be between 1 and %d\n", n);
                    break;
                }
                long long start = current_time_us();
                bellmanFord(src, graph, n);
                long long end = current_time_us();
                printf("\nTime taken: %lldμs\n", end - start);
                break;
                
            case 3:
                printf("Exiting...\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}