#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#define N 100
#define INF INT_MAX
void fillInf(int graph[][N], int n);
void getMatrix(int graph[][N], int n);
void show2DMatrix(int graph[][N], int n);
void bellmanFord(int src, int graph[][N], int n);
void printPath(int parent[], int j);
long long current_time_us();
void fillInf(int graph[][N], int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) graph[i][j] = 0;
            else graph[i][j] = INF;
        }
    }
}
void getMatrix(int a[][N], int n) {
    int w, x, y;
    printf("Enter edge information as 'x y weight' (-1 -1 -1 to exit):\n");
    for (int i = 0; i < n * (n - 1); i++) {
        scanf("%d", &x);
        scanf("%d", &y);
        scanf("%d", &w);
        if (x == -1 && y == -1) return;
        if (x < 1 || x > n || y < 1 || y > n) {
            printf("Invalid vertices! Please enter values between 1 and %d\n", n);
            i--;
            continue;
        }
        a[x][y] = w;
    }
}
void show2DMatrix(int graph[][N], int n) {
    printf("   ");
    for (int i = 1; i <= n; i++) printf("%4d", i);
    printf("\n");
    for (int i = 1; i <= n; i++) {
        printf("%2d ", i);
        for (int j = 1; j <= n; j++) {
            if (graph[i][j] == INF) printf("   ∞");
            else printf("%4d", graph[i][j]);
        }
        printf("\n");
    }
}
void printDistTable(int dist[][N], int n, int iterations) {
    printf("\n%5s", "k");
    for (int i = 1; i <= n; i++) printf("%4d", i);
    printf("\n");
    for (int i = 0; i <= n; i++) printf("----");
    printf("\n");
    for (int k = 1; k < iterations; k++) {
        printf("%4d |", k);
        for (int i = 1; i <= n; i++) {
            if (dist[k][i] == INF) printf("  ∞ ");
            else printf("%3d ", dist[k][i]);
        }
        printf("\n");
    }
}
void printPath(int parent[], int j) {
    if (parent[j] == -1) return;
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}
void bellmanFord(int src, int graph[][N], int n) {
    int dist[N][N];
    int parent[N];
    for (int i = 1; i <= n; i++) parent[i] = -1;
    for (int i = 1; i <= n; i++) {
        if (i == src) dist[1][i] = 0;
        else {
            dist[1][i] = graph[src][i];
            if (graph[src][i] != INF) parent[i] = src;
        }
    }
    for (int k = 2; k <= n; k++) {
        for (int i = 1; i <= n; i++) dist[k][i] = dist[k-1][i];
        for (int u = 1; u <= n; u++) {
            if (u != src) {
                bool has_incoming = false;
                for (int i = 1; i <= n; i++) {
                    if (graph[i][u] != INF) {
                        has_incoming = true;
                        break;
                    }
                }
                if (has_incoming) {
                    for (int i = 1; i <= n; i++) {
                        if (graph[i][u] != INF && dist[k-1][i] != INF) {
                            if (dist[k][u] > dist[k-1][i] + graph[i][u]) {
                                dist[k][u] = dist[k-1][i] + graph[i][u];
                                parent[u] = i;
                            }
                        }
                    }
                }
            }
        }
    }
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
    printf("\ndist[1..%d] after each iteration:\n", n);
    printDistTable(dist, n, n);
    if (has_negative_cycle) printf("\nWARNING: Graph contains negative weight cycle!\n");
    else {
        printf("\nFinal shortest distances and paths from source vertex %d:\n", src);
        for (int i = 1; i <= n; i++) {
            if (i != src) {
                if (dist[n][i] == INF) printf("Vertex %d: INF (unreachable)\n", i);
                else {
                    printf("Vertex %d: Distance = %d, Path: %d", i, dist[n][i], src);
                    printPath(parent, i);
                    printf("\n");
                }
            }
        }
    }
}
long long current_time_us() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}
int main() {
    int n, graph[N][N], src, choice;
    bool graphCreated = false;
    while(1) {
        printf("\n1. Create Graph\n2. Find Shortest Paths (Bellman-Ford)\n3. Exit\nEnter your choice: ");
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
