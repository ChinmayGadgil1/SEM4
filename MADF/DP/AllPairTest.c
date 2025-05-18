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

void AllPair(int **cost, int **A, int **p, int n){
    bool **changed = (bool **)malloc((n+1) * sizeof(bool *));
    for (int i = 1; i <= n; i++){
        changed[i] = (bool *)malloc((n+1) * sizeof(bool));
        for (int j = 1; j <= n; j++)
            changed[i][j] = false;
    }

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (i == j || cost[i][j] == INFINITY)
                p[i][j] = -1;
            else
                p[i][j] = i;
        }
    }

    printf("A^0:\n");
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (A[i][j] == INFINITY)
                printf(" ∞  ");
            else
                printf(" %-3d", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    printf("P^0:\n");
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (p[i][j] != -1)
                printf(" %-3d", p[i][j]);
            else
                printf(" -  ");
        }
        printf("\n");
    }
    printf("\n");
    
    for (int k = 1; k <= n; k++){
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                if (A[i][k] != INFINITY && A[k][j] != INFINITY && 
                    A[i][j] > (A[i][k] + A[k][j])){
                    A[i][j] = A[i][k] + A[k][j];
                    p[i][j] = p[k][j];
                    changed[i][j] = true;
                }
            }
        }
        printf("A^%d:\n", k);
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
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
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
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
        
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                changed[i][j] = false;
            }
        }
    }
    for (int i = 1; i <= n; i++){
        free(changed[i]);
    }
    free(changed);
}

char *getPath(int **p, int i, int j){
    if (i == j){
        char *path = (char *)malloc(10 * sizeof(char)); 
        sprintf(path, "%d", i);
        return path;
    }
    if (p[i][j] == -1){
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

int main(){
    int n, choice;
    int **cost = NULL, **A = NULL, **p = NULL;

    while(1){
        printf("\n1. Create Graph\n2. Find All Pair Shortest Path\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                if(cost != NULL){
                    for(int i = 0; i <= n; i++){
                        free(cost[i]);
                        free(A[i]);
                        free(p[i]);
                    }
                    free(cost);
                    free(A);
                    free(p);
                }
                
                printf("Enter the number of vertices: ");
                scanf("%d", &n);
                
                cost = (int **)malloc((n+1) * sizeof(int *));
                A = (int **)malloc((n+1) * sizeof(int *));
                p = (int **)malloc((n+1) * sizeof(int *));

                for (int i = 0; i <= n; i++){
                    cost[i] = (int *)malloc((n+1) * sizeof(int));
                    A[i] = (int *)malloc((n+1) * sizeof(int));
                    p[i] = (int *)malloc((n+1) * sizeof(int));
                }

                for (int i = 0; i <= n; i++){
                    for (int j = 0; j <= n; j++){
                        cost[i][j] = INFINITY;
                    }
                }
                
                for (int i = 1; i <= n; i++){
                    cost[i][i] = 0;
                }

                int max_edges = n*(n-1), origin, destin, weight;
                printf("Enter edges and cost (origin destination weight) (-1 -1 -1 to exit):\n");
                for (int i = 1; i <= max_edges; i++){
                    scanf("%d%d%d", &origin, &destin, &weight);
                    if ((origin == -1) && (destin == -1)) break;
                    if (origin > n || destin > n || origin < 1 || destin < 1){
                        printf("Invalid edge! Enter values between 1 and %d\n", n);
                        i--;
                    }
                    else{
                        cost[origin][destin] = weight;
                    }
                }
                break;

            case 2:
                if(cost == NULL){
                    printf("Please create graph first!\n");
                    break;
                }
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= n; j++)
                        A[i][j] = cost[i][j];

                long long start = current_time_us();
                AllPair(cost, A, p, n);
                long long end = current_time_us();
                printf("\nTime taken: %lldμs\n", end - start);

                printf("Final Shortest Paths:\n");
                printf("+---------+---------+---------+------------------+\n");
                printf("| Source  | Dest    | Length  | Path             |\n");
                printf("+---------+---------+---------+------------------+\n");
                for (int i = 1; i <= n; i++){
                    for (int j = 1; j <= n; j++){
                        char *path = getPath(p, i, j);
                        if (A[i][j] == INFINITY)
                            printf("| %-7d | %-7d | %-7s | %-16s |\n", i, j, "∞", path);
                        else
                            printf("| %-7d | %-7d | %-7d | %-16s |\n", i, j, A[i][j], path);
                        free(path);
                    }
                }
                printf("+---------+---------+---------+------------------+\n");
                break;

            case 3:
                if(cost != NULL){
                    for(int i = 0; i <= n; i++){
                        free(cost[i]);
                        free(A[i]);
                        free(p[i]);
                    }
                    free(cost);
                    free(A);
                    free(p);
                }
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
