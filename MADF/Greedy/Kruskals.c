#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>
#define infinity INT_MAX
#define MAX 20
int n;

long long current_time_us() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

struct Edge {
    int u;
    int v;
    int cost;
};

struct Heap {
    struct Edge *array;
    int size;
    int capacity;
};

struct Heap* createHeap(int capacity) {
    struct Heap* heap = (struct Heap*)malloc(sizeof(struct Heap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (struct Edge*)malloc(capacity * sizeof(struct Edge));
    return heap;
}

void Adjust(struct Edge a[], int i, int n) {
    int j = 2 * i;
    struct Edge item = a[i];
    
    while (j <= n) {
        if ((j < n) && (a[j].cost > a[j + 1].cost)) {
            j = j + 1;
        }
        
        if (item.cost <= a[j].cost) {
            break;
        }
        
        a[j / 2] = a[j];
        j = 2 * j;
    }
    
    a[j / 2] = item;
}

void Heapify(struct Edge a[], int n) {
    for (int i = n / 2; i >= 1; i--) {
        Adjust(a, i, n);
    }
}

int DelMin(struct Edge a[], int n, struct Edge* x) {
    if (n == 0) {
        printf("heap is empty\n");
        return 0; 
    }
    
    *x = a[1];
    a[1] = a[n];
    Adjust(a, 1, n - 1);
    return 1;  // true
}

int Find(int parent[], int i) {
    while (parent[i] > 0) {
        i = parent[i];
    }
    return i;
}

void Union(int parent[], int j, int k) {
    parent[j] = k;
}

void create(int cost[MAX][MAX], struct Edge edges[], int* edge_count) {
    int max_edges, u, v, weight;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    max_edges = n * (n - 1) / 2;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cost[i][j] = infinity;
        }
    }

    *edge_count = 0;
    printf("Enter edges with weight (-1 -1 -1 to quit): \n");
    for (int i = 1; i <= max_edges; i++) {
        scanf("%d%d%d", &u, &v, &weight);
        if ((u == -1) && (v == -1)) {
            break;
        }
        if (u > n || v > n || u < 1 || v < 1) {
            printf("Invalid edge\n");
            i--;
        } else {
            cost[u][v] = weight;
            cost[v][u] = weight;
            
            (*edge_count)++;
            edges[*edge_count].u = u;
            edges[*edge_count].v = v;
            edges[*edge_count].cost = weight;
        }
    }
}

int Kruskal(struct Edge E[], int cost[MAX][MAX], int n, int t[MAX][3], int edge_count) {
    Heapify(E, edge_count);
    
    int parent[MAX];
    for (int i = 1; i <= n; i++) {
        parent[i] = -1;
    }

    int i = 0;
    int mincost = 0;
 
    while ((i < n - 1) && (edge_count > 0)) {

        struct Edge minEdge;
        if (DelMin(E, edge_count, &minEdge)) {
            edge_count--;
            int u = minEdge.u;
            int v = minEdge.v;
            
            int j = Find(parent, u);
            int k = Find(parent, v);
    
            if (j != k) {
      
                i = i + 1;
                

                t[i][1] = u;
                t[i][2] = v;
                

                mincost = mincost + cost[u][v];
                

                Union(parent, j, k);
            }
        }
    }
    

    if (i != n - 1) {
        printf("No spanning tree\n");
        return -1;
    } else {
        return mincost;
    }
}

int main() {
    int cost[MAX][MAX];
    int t[MAX][3];
    struct Edge edges[MAX * MAX]; 
    int edge_count = 0;
    int choice,mincost;
    long long start,end;
    printf("\n1. Create graph\n");
    printf("2. Find Minimum Spanning Tree\n");
    printf("3. Exit\n");
    while (1)
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            create(cost,edges,&edge_count);
            break;
        case 2:
            start = current_time_us();
            mincost = Kruskal(edges,cost,n,t,edge_count);
            end = current_time_us();
            printf("\nTime taken: %lldμs\n", end - start);
            printf("Mincost: %d\n", mincost);
            for (int i = 1; i <= n - 1; i++)
            {
                printf("%d - %d\n", t[i][1], t[i][2]);
            }
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice\n");
            break;
        }
        
    }
    
    
    return 0;
}