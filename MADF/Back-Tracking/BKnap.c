#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<sys/time.h>

long long current_time_us(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}


struct PAIR
{
    double p;
    double w;
    double pw;
};
int n;
double fp = -1;
double fw = -1;
double m;
double *p, *w;
int *x, *y;
void print(int *a, int n)
{
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
void sort()
{
    struct PAIR *pairs = (struct PAIR *)malloc((n + 1) * sizeof(struct PAIR));
    for (int i = 1; i <= n; i++)
    {
        pairs[i].p = p[i];
        pairs[i].w = w[i];
        pairs[i].pw = p[i] / (double)w[i];
    }
    for (int i = 1; i <= n - 1; i++)
    {
        int p = 0;
        for (int j = 1; j <= n - i; j++)
        {
            if (pairs[j].pw < pairs[j + 1].pw)
            {
                struct PAIR t = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = t;
                p++;
            }
        }
        if (p == 0)
        {
            break;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        p[i] = pairs[i].p;
        w[i] = pairs[i].w;
    }
}

double Bound(int k, double cp, double cw)
{
    double a = cp;
    double b = cw;
    for (int i = k + 1; i <= n; i++)
    {
        b += w[i];
        if (b < m)
        {
            a += p[i];
        }
        else
        {
            return a + (w[i] - (b - m)) * p[i] / w[i];
        }
    }
    return a;
}

void O1Knapsack(int k, double cp, double cw)
{
    static int s = 0;
    if (k > n)
    {
        if (cp > fp)
        { 
            fp = cp;
            fw = cw;
            for (int i = 1; i <= n; i++)
            {
                x[i] = y[i];
            }
            printf("New Optimal solution %d: Profit = %d, Weight = %d, Solution Vector: [", ++s, (int)fp, (int)fw);

            for (int i = 1; i <= n; i++)
            {

                printf("%d%s", x[i], (i == n) ? "]\n" : ", ");
            }
        }
        return;
    }
    printf("Node: [%d], Current Profit: %d, Current Weight: %d\n", k, (int)cp, (int)cw);
    double bound = Bound(k, cp, cw);
    if (cw + w[k] <= m)
    {
        y[k] = 1; 
        printf(" Including item %d (Lchild of [%d]):\n", k, k);
        O1Knapsack(k + 1, cp + p[k], cw + w[k]);
    }
    else{
        printf("Weight of item %d exceeds capacity therefore we exclude it.\n", k);
    }
    if (bound >= fp)
    {
        y[k] = 0; 
        printf(" Excluding item %d (Rchild of [%d]), Bound = %f\n", k, k, bound);
        O1Knapsack(k + 1, cp, cw);
    }
    else
    {
        printf(" Bound at item %d (Rchild of [%d]), Bound = %f <  %f\n", k, k, bound, fp);
    }
}

double *p = NULL, *w = NULL;
int *x = NULL, *y = NULL;

void inputData() {
    printf("Enter the number of Objects: ");
    scanf("%d", &n);
    
    if(p != NULL) free(p);
    if(w != NULL) free(w);
    if(x != NULL) free(x);
    if(y != NULL) free(y);
    
    p = (double *)malloc((n + 1) * sizeof(double));
    printf("Enter the profits of Objects: ");
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &p[i]);
    }
    
    w = (double *)malloc((n + 1) * sizeof(double));
    printf("Enter the weights of Objects: ");
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &w[i]);
    }

    printf("Enter the size of the knapsack: ");
    scanf("%lf", &m);
    
    x = (int *)malloc((n + 1) * sizeof(int));
    y = (int *)malloc((n + 1) * sizeof(int));
}

void solveKnapsack() {
    if(p == NULL || w == NULL || x == NULL || y == NULL) {
        printf("Please input data first!\n");
        return;
    }

    fp = -1;
    fw = -1;
    
    sort();
    double bound = Bound(0, 0.0, 0.0);
    printf("Initial Bound=%lf\n", bound);
    long long start = current_time_us();
    O1Knapsack(1, 0.0, 0.0);
    long long end = current_time_us();
    printf("\nFinal Optimal solution: \n[k, cp, cw] = [%d, %d, %d]\nSolution Vector: ", n + 1, (int)fp, (int)fw);
    printf("[");
    for (int i = 1; i <= n; i++) {
        printf("%d%s", x[i], (i == n) ? "]\n" : ", ");
    }
    printf("Time taken: %lldμs\n", end - start);
}

int main() {
    int choice;
    do {
        printf("\n");
        printf("1. Input Data\n");
        printf("2. Solve Knapsack\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                inputData();
                break;
            case 2:
                if(p == NULL || w == NULL || x == NULL || y == NULL) {
                    printf("Please input data first!\n");
                    break;
                }
                solveKnapsack();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 3);
    
    if(p != NULL) free(p);
    if(w != NULL) free(w);
    if(x != NULL) free(x);
    if(y != NULL) free(y);
    
    return 0;
}