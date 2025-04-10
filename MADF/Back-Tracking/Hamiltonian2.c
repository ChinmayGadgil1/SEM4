#include <stdio.h>
#define MAX 100
#define TRUE 1
#define FALSE 0

int G[MAX][MAX];
int leafCount = 0, solnCount = 0, startVertex = 0;
int soln[MAX][MAX];
int solnLen[MAX];

void printPath(int x[], int n, int flag) {
    if (flag == TRUE)
        printf("\e[1m %d\e[m", x[1]);
    else {
        printf("%d", x[1]);
    }
    for (int i = 2; i < n; i++) {
        if (flag == TRUE)
            printf("\e[1m -> %d\e[m", x[i]);
        else
            printf(" -> %d", x[i]);
    }
    if (flag == TRUE)
        printf("\e[1m -> %d -> %d\e[m", x[n], x[1]);
    else
        printf(" -> %d ", x[1]);
}

void store_solution(int x[], int n) {
    for (int i = 1; i <= n; i++) {
        soln[solnCount][i] = x[i];
    }
    solnLen[solnCount] = n;
    solnCount++;
}

void print_solutions() {
  
    for (int i = 0; i < solnCount; i++) {
        printf("%d: ", i + 1);
        for (int j = 1; j <= solnLen[i]; j++) {
            if (j == solnLen[i]) {
                printf("\e[1m%d -> %d\e[m", soln[i][j], soln[i][1]);
            } else {
                printf("\e[1m%d -> \e[m", soln[i][j]);
            }
        }
        printf("\n");
    }
}

void nextval(int x[], int n, int k) {
    int j, i;
    do {
        x[k] = (x[k] + 1) % (n + 1);
        if (x[k] == 0)
            return;
        if (G[x[k - 1]][x[k]] != 0) {
            for (j = 1; j < k; j++) {
                if (x[j] == x[k]) {
                    printf("Leaf node %3d : ", ++leafCount);
                    for (i = 1; i <= k; i++) {
                        if (i != k)
                            printf("%d -> ", x[i]);
                        else
                            printf("%d (Bound)\n", x[i]);
                    }
                    break;
                }
            }
            if (j == k) {
                if ((k < n) || (k == n && G[x[n]][x[1]] != 0)) {
                    return;
                }
            }
        }
    } while (TRUE);
}

void Hamiltonian(int x[], int n, int k) {
    int notLeaf = FALSE;
    do {
        nextval(x, n, k);
        if (x[k] != 0)
            notLeaf = TRUE;
        if (x[k] == 0) {
            if (notLeaf == FALSE) {
                printf("Leaf node %3d : ", ++leafCount);
                printPath(x, k, notLeaf);
                printf(" (Bound)\n");
            }
            return;
        }
        if (k == n) {
            printf("\e[1mLeaf node %3d: \e[m", ++leafCount);
            printPath(x, n, notLeaf);
            printf("\e[1m (Solution)\e[m\n");
            store_solution(x, n);
            if (startVertex == 1)
                ++solnCount;
        } else {
            Hamiltonian(x, n, k + 1);
        }
    } while (TRUE);
}

int main() {
    int n, x[MAX], k;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix (0/1):\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            scanf("%d", &G[i][j]);
    }
    solnCount = 0;
    
        x[1] = 1;
        for (int i = 2; i <= n; i++)
            x[i] = 0;
        Hamiltonian(x, n, 2);
    print_solutions();
    printf("\nTotal number of solutions: %d\n", solnCount);
    return 0;
}
