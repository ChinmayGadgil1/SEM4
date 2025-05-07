#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
int n, cnt = 1, m;
int *w, *x;

struct node {
    struct node *lchild;
    int s, k, r, cn, fl;
    struct node *rchild;
};

long long current_time_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

struct node *root;

void showarr(int n, int *a) {
    printf("{");
    for (int j = 0; j < n; j++) {
        printf("%d%c", a[j], j == n - 1 ? '}' : ',');
    }
    printf("\n");
}

int sumarr(int n, int *a) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

void zeroarr(int n, int *a) {
    for (int j = 0; j < n; j++) {
        a[j] = 0;
    }
}

int is_solution(int k) {
    int sum = 0;
    for (int i = 1; i <= k; i++) {
        if (x[i] == 1) {
            sum += w[i];
        }
    }
    return (sum == m);
}

void print_solution() {
    printf("Subset %d: ", cnt++);
    for (int i = 1; i <= n; i++) {
        if (x[i] == 1) {
            printf("%d ", w[i]);
        }
    }
    printf("\n");
}

struct node *SumOfSub(int s, int k, int r) {
    struct node *tmp =(struct node *) malloc(sizeof(struct node));
    tmp->s = s;
    tmp->k = k;
    tmp->r = r;
    tmp->cn = cnt;
    tmp->fl = 0;
    tmp->lchild = NULL;
    tmp->rchild = NULL;

    if (k > n) {
        return tmp;
    }

    if (is_solution(k-1)) {
        tmp->fl = 1;
        print_solution();
    }

    x[k] = 1;
    if (s + w[k] <= m) {
        if (s + w[k] == m) {
            struct node *leftchild =(struct node*) malloc(sizeof(struct node));
            leftchild->s = s + w[k];
            leftchild->k = k + 1;
            leftchild->r = r - w[k];
            leftchild->cn = cnt;
            leftchild->fl = 1;
            leftchild->lchild = NULL;
            leftchild->rchild = NULL;
            printf("Subset %d: ", cnt++);
            for (int i = 1; i <= k; i++) {
                if (x[i] == 1) {
                    printf("%d ", w[i]);
                }
            }
            printf("\n");
            tmp->lchild = leftchild;
        }
        else if (k < n && s + w[k] + w[k+1] <= m) {
            tmp->lchild = SumOfSub(s + w[k], k + 1, r - w[k]);
        }
    }

    x[k] = 0;
    if ((s + r - w[k] >= m) && (k < n && s + w[k+1] <= m)) {
        tmp->rchild = SumOfSub(s, k + 1, r - w[k]);
    }

    return tmp;
}

void print_tree(struct node *root, int level) {
    if (root == NULL)
        return;

    for (int i = 1; i <= level; i++)
        printf("    ");

    printf("Node(s=%d, k=%d, r=%d)", root->s, root->k, root->r);
    
    if (root->fl == 1)
        printf(" [SOLUTION]");
    
    printf("\n");

    print_tree(root->lchild, level + 1);
    print_tree(root->rchild, level + 1);
}


int main() {
    int choice;
    
    do {
        printf("\n=== Sum of Subsets Menu ===\n");
        printf("1. Find subsets with given sum\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                printf("Enter the number of elements in set: ");
                scanf("%d", &n);
                printf("Enter m: ");
                scanf("%d", &m);
                w = (int*)malloc((n + 1) * sizeof(int));
                x = (int*)malloc((n + 1) * sizeof(int));
                zeroarr(n + 1, x);
                printf("Enter %d elements: ", n);
                for (int i = 1; i <= n; i++) {
                    scanf("%d", &w[i]);
                }
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n - i; j++) {
                        if (w[j] > w[j + 1]) {
                            int temp = w[j];
                            w[j] = w[j + 1];
                            w[j + 1] = temp;
                        }
                    }
                }
                printf("\nSolutions: \n");
                int s = 0, k = 1, r = 0;
                for (int i = 1; i <= n; i++) {
                    r += w[i];
                }
                if (w[1] > m || r < m) {
                    printf("No solution exists.\n");
                } else {
                    long long start = current_time_us();
                    root = SumOfSub(s, k, r);
                    long long end = current_time_us();
                    printf("\nTime taken: %lldμs\n", end - start);
                    printf("\nState Space Tree:\n");
                    print_tree(root, 1);
                }
                cnt = 1;
                free(w);
                free(x);
                break;
            }
            case 2:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 2);

    return 0;
}
