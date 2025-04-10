#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

long long current_time_us() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

#define INFINITY INT_MAX

int n;
bool **G;
int *x;
bool solutionFound;
int cycleCount = 0;

void initializeGraph() {
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    
    G = (bool **)malloc((n+1) * sizeof(bool *));
    for (int i = 0; i <= n; i++) {
        G[i] = (bool *)malloc((n+1) * sizeof(bool));
        for (int j = 0; j <= n; j++) {
            G[i][j] = false;
        }
    }
    
    x = (int *)malloc((n+1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        x[i] = 0;
    }
    
    int max_edges = n*(n-1)/2, origin, destin;
    printf("Enter the edges (origin, destination) (-1,-1 to exit):\n");
    for (int i = 1; i <= max_edges; i++) {
        scanf("%d%d", &origin, &destin);
        if ((origin == -1) && (destin == -1)) {
            break;
        }
        if (origin > n || destin > n || origin < 1 || destin < 1) {
            printf("Invalid edge! Please enter values between 1 and %d\n", n);
            i--;
        } else {
            G[origin][destin] = true;
            G[destin][origin] = true;
        }
    }
}

void displayGraph() {
    printf("\nGraph Adjacency Matrix:\n");
    printf("    ");
    for (int i = 1; i <= n; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    for (int i = 1; i <= n; i++) {
        printf("%d | ", i);
        for (int j = 1; j <= n; j++) {
            printf("%d ", G[i][j] ? 1 : 0);
        }
        printf("\n");
    }
}

int NextValue(int k) {
    do {
        x[k] = (x[k] + 1) % (n + 1);
        if (x[k] == 0) return 0;
        
        if (k == 1 || G[x[k-1]][x[k]]) {
        
            bool distinct = true;
            for (int j = 1; j < k; j++) {
                if (x[j] == x[k]) {
                    distinct = false;
                    break;
                }
            }

            if (distinct && (k < n || (k == n && G[x[n]][x[1]]))) {
                return x[k];
            }
        }
    } while (true);
}

void displayHamiltonianCycle() {
    printf("\nHamiltonian Cycle %d:\n", ++cycleCount);
    printf("Path: ");
    for (int i = 1; i <= n; i++) {
        printf("%d ", x[i]);
    }
    printf("%d\n", x[1]); 
}

void Hamiltonian(int k) {
   
    do {
        x[k] = NextValue(k);
        
        if (x[k] == 0) return;
        
        if (k == n) {
            displayHamiltonianCycle();
        } else {
            Hamiltonian(k + 1);
        }
    } while (true);
}

void findHamiltonianCycles() {
    printf("\nFinding Hamiltonian Cycles...\n");
    x[1] = 1;
    
    long long start = current_time_us();
    Hamiltonian(2); // Start from the second vertex since the first is fixed
    long long end = current_time_us();
    
    if (cycleCount == 0) {
        printf("\nNo Hamiltonian cycles found in this graph.\n");
    } else {
        printf("\nTotal Hamiltonian cycles found: %d\n", cycleCount);
    }
    
    printf("Time taken: %lldμs\n", end - start);
}


void cleanup() {
    for (int i = 0; i <= n; i++) {
        free(G[i]);
    }
    free(G);
    free(x);
}

int main() {
    
    int choice;
    do {
        printf("\nChoose an algorithm to run:\n");
        printf("1. Create graph\n");
        printf("2. Find Hamiltonian cycle\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                initializeGraph();
                displayGraph();
                break;
            case 2:
                printf("Finding Hamiltonian cycles...\n");
                findHamiltonianCycles();

                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 3);
    
    cleanup();
    return 0;
}