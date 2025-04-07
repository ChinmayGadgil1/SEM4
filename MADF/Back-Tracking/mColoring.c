#include<stdio.h>
#include<sys/time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

long long current_time_us(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

#define INFINITY INT_MAX

int n;
int m;
bool **G;
int *x;
bool solutionFound;

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
    
    int max_edges = n*(n-1), origin, destin;
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

int NextValue(int k) {
    do {
        x[k] = (x[k] + 1) % (m + 1);
        if (x[k] == 0) return 0;
        
        bool valid = true;
        for (int j = 1; j <= n; j++) {
            if (G[k][j] && x[k] == x[j]) {
                valid = false;
                break;
            }
        }
        
        if (valid) return x[k];
    } while (true);
}

void displaySolution() {
    printf("\nSolution found with %d colors:\n", m);
    printf("Vertex:\t");
    for (int i = 1; i <= n; i++) {
        printf("%d\t", i);
    }
    printf("\nColor:\t");
    for (int i = 1; i <= n; i++) {
        printf("%d\t", x[i]);
    }
    printf("\n");
}

void mColoring(int k) {
    if (solutionFound) return;
    
    do {
        x[k] = NextValue(k);
        
        if (x[k] == 0) return;
        
        if (k == n) {
            displaySolution();
            solutionFound = true;
            return;
        } else {
            mColoring(k + 1);
        }
    } while (!solutionFound);
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

void resetColors() {
    for (int i = 1; i <= n; i++) {
        x[i] = 0;
    }
}

void cleanup() {
    for (int i = 0; i <= n; i++) {
        free(G[i]);
    }
    free(G);
    free(x);
}

int findChromaticNumber() {
    long long totalTime = 0;
    
    for (m = 1; m <= n; m++) {
        printf("\nTrying with %d colors...\n", m);
        solutionFound = false;
        resetColors();
        
        long long start = current_time_us();
        mColoring(1);
        long long end = current_time_us();
        
        long long timeForThisAttempt = end - start;
        totalTime += timeForThisAttempt;
        printf("Time for %d colors: %lldμs\n", m, timeForThisAttempt);
        
        if (solutionFound) {
            printf("\n-----------------------------------");
            printf("\nChromatic number is %d", m);
            printf("\nTotal time taken: %lldμs", totalTime);
            printf("\n-----------------------------------\n");
            return m;
        }
    }
    
    return -1; 
}

int main() {
    printf("Graph Coloring Algorithm - Chromatic Number Finder\n");
    printf("================================================\n");
    
    initializeGraph();
    displayGraph();
    
    printf("\nFinding chromatic number automatically...\n");
    int chromaticNumber = findChromaticNumber();
    
    cleanup();
    return 0;
}