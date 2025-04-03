#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include<stdio.h>
#include<sys/time.h>


long long current_time_us(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}



#define INFINITY 1000

void AllPair(int **cost, int **A, int **p, int n)
{
    bool **changed = (bool **)malloc((n+1) * sizeof(bool *));
    for (int i = 1; i <= n; i++)
    {
        changed[i] = (bool *)malloc((n+1) * sizeof(bool));
        for (int j = 1; j <= n; j++)
            changed[i][j] = false; // Initialize all elements to false
    }
    // Initialize p array
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j || cost[i][j] == INFINITY)
                p[i][j] = -1; // No predecessor
            else
                p[i][j] = i; // predecessor is i
        }
    }
    // Print initial adjacency matrix (A0)
    printf("A^0:\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (A[i][j] == INFINITY)
                printf(" ∞  ");
            else
                printf(" %-3d", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    printf("P^0:\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (p[i][j] != -1)
                printf(" %-3d", p[i][j]);
            else
                printf(" -  ");
        }
        printf("\n");
    }
    printf("\n");
    
    // Floyd Warshall algorithm
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                // If there is a shorter path through k, update A and p
                if (A[i][k] != INFINITY && A[k][j] != INFINITY && 
                    A[i][j] > (A[i][k] + A[k][j]))
                {
                    A[i][j] = A[i][k] + A[k][j];
                    p[i][j] = p[k][j]; // Update predecessor
                    changed[i][j] = true;
                }
            }
        }
        // Print intermediate adjacency matrices
        printf("A^%d:\n", k);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (A[i][j] == INFINITY)
                    printf(" ∞  ");
                else if (changed[i][j])
                    printf("[%-2d]", A[i][j]);
                else
                    printf(" %-3d", A[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        
        printf("P^%d:\n", k);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (p[i][j] == -1)
                    printf(" -  ");
                else if (changed[i][j])
                    printf("[%-2d]", p[i][j]);
                else
                    printf(" %-3d", p[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        
        // Reset changed array
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                changed[i][j] = false;
            }
        }
    }
    // Free memory for changed array
    for (int i = 1; i <= n; i++)
    {
        free(changed[i]);
    }
    free(changed);
}

char *getPath(int **p, int i, int j)
{
    if (i == j)
    {
        char *path = (char *)malloc(10 * sizeof(char)); 
        sprintf(path, "%d", i);
        return path;
    }
    if (p[i][j] == -1)
    {
        char *path = (char *)malloc(10 * sizeof(char));
        sprintf(path, "No path");
        return path;
    }

    char *intermediatePath = getPath(p, i, p[i][j]);
    char *path = (char *)malloc((strlen(intermediatePath) + 10) * sizeof(char));      
    sprintf(path, "%s->%d", intermediatePath, j);
    free(intermediatePath);
    return path;
}

int main()
{
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
  
    int **cost = (int **)malloc((n+1) * sizeof(int *));
    int **A = (int **)malloc((n+1) * sizeof(int *));
    int **p = (int **)malloc((n+1) * sizeof(int *));

    // Allocate memory for 1-based indexing
    for (int i = 0; i <= n; i++)
    {
        cost[i] = (int *)malloc((n+1) * sizeof(int));
        A[i] = (int *)malloc((n+1) * sizeof(int));
        p[i] = (int *)malloc((n+1) * sizeof(int));
    }

    // Initialize cost matrix
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cost[i][j] = INFINITY;
        }
    }
    
    for (int i = 1; i <= n; i++)
    {
        cost[i][i] = 0;
    }
    
    int max_edges = n*(n-1), origin, destin, weight;
    printf("Enter the edges and cost (origin, destination, weight) (-1,-1,-1 to exit):\n");
    for (int i = 1; i <= max_edges; i++)
    {
        scanf("%d%d%d", &origin, &destin, &weight);
        if ((origin == -1) && (destin == -1))
        {
            break;
        }
        if (origin > n || destin > n || origin < 1 || destin < 1)
        {
            printf("Invalid edge! Please enter values between 1 and %d\n", n);
            i--;
        }
        else
        {
            cost[origin][destin] = weight;
        }
    }
    
    // Copy cost matrix to A
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            A[i][j] = cost[i][j];
        }
    }

    // Perform Floyd Warshall algorithm
    long long start = current_time_us();

    AllPair(cost, A, p, n);
    long long end = current_time_us();
    printf("\nTime taken: %lldμs\n", end - start);

    // Print final results
    printf("Final Shortest Paths:\n");
    printf("+---------+---------+---------+------------------+\n");
    printf("| Source  | Dest    | Length  | Path             |\n");
    printf("+---------+---------+---------+------------------+\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            char *path = getPath(p, i, j);
            if (A[i][j] == INFINITY)
                printf("| %-7d | %-7d | %-7s | %-16s |\n", i, j, "∞", path);
            else
                printf("| %-7d | %-7d | %-7d | %-16s |\n", i, j, A[i][j], path);
            free(path);
        }
    }
    printf("+---------+---------+---------+------------------+\n");

    // Free dynamically allocated memory
    for (int i = 0; i <= n; i++)
    {
        free(cost[i]);
        free(A[i]);
        free(p[i]);
    }
    free(cost);
    free(A);
    free(p);
    return 0;
}