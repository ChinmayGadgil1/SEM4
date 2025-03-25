#include <stdio.h>
#include<sys/time.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
int w[MAX][MAX];
int c[MAX][MAX];
int r[MAX][MAX];
long long current_time_us(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

char* iden[MAX];

int Find(int c[MAX][MAX], int r[MAX][MAX], int i, int j)
{
    int l;
    int min = 9999;
    for (int m = r[i][j - 1]; m <= r[i + 1][j]; m++)
    {
        if (c[i][m - 1] + c[m][j] < min)
        {
            min = c[i][m - 1] + c[m][j];
            l = m;
        }
    }
    return l;
}

void preorder(int r[MAX][MAX], int i, int j, char *identifiers[])
{
    if (i >= j)
        return;
    if (r[i][j] == 0)
        return;
    printf(" %s(k=%d) ", identifiers[r[i][j]], r[i][j]);
    preorder(r, i, r[i][j] - 1, identifiers);
    preorder(r, r[i][j], j, identifiers);
}

void inorder(int r[MAX][MAX], int i, int j, char *identifiers[])
{
    if (i >= j)
        return;
    if (r[i][j] == 0)
        return;
    inorder(r, i, r[i][j] - 1, identifiers);
    printf(" %s(k=%d) ", identifiers[r[i][j]], r[i][j]);
    inorder(r, r[i][j], j, identifiers);
}

void postorder(int r[MAX][MAX], int i, int j, char *identifiers[])
{
    if (i >= j)
        return;
    if (r[i][j] == 0)
        return;
    postorder(r, i, r[i][j] - 1, identifiers);
    postorder(r, r[i][j], j, identifiers);
    printf(" %s(k=%d) ", identifiers[r[i][j]], r[i][j]);
}
void OBST(int p[], int q[], int n)
{
    for (int i = 0; i <= n - 1; i++)
    {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
        w[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
        r[i][i + 1] = i + 1;
        c[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
    }
    w[n][n] = q[n];
    r[n][n] = 0;
    c[n][n] = 0;

    for (int i = 0; i <= n; i++)
    {
        printf("w[%d][%d]=%d ", i, i, w[i][i]);
    }
    printf("\n");
    for (int i = 0; i <= n; i++)
    {
        printf("c[%d][%d]=%d ", i, i, c[i][i]);
    }
    printf("\n");
    for (int i = 0; i <= n; i++)
    {
        printf("r[%d][%d]=%d ", i, i, r[i][i]);
    }
    printf("\n");

    for (int m = 2; m <= n; m++)
    {
        for (int i = 0; i <= n - m; i++)
        {
            int j = i + m;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            int k = Find(c, r, i, j);
            c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
            r[i][j] = k;
        }
    }
    int j;
    for (int i = 0; i <= n; i++)
    {
        printf("\t\t %d ", i);
    }
    for (int d = 0; d <= n; d++)
    {
        printf("\n");
        printf("j-i=%d ", d);
        j = 0;
        printf("\t\tw[%d][%d] = %2d ", j, d, w[j][d]);
        j++;
        for (int i = d + 1; i <= n; i++)
        {
            printf("\tw[%d][%d] = %2d", j, i, w[j][i]);
            j++;
        }
        printf("\n");
        j = 0;
        printf("\t\tc[%d][%d] = %2d", j, d, c[j][d]);
        j++;
        for (int i = d + 1; i <= n; i++)
        {
            printf("\tc[%d][%d] = %2d", j, i, c[j][i]);
            j++;
        }
        printf("\n");
        j = 0;
        printf("\t\tr[%d][%d] = %2d", j, d, r[j][d]);
        j++;
        for (int i = d + 1; i <= n; i++)
        {
            printf("\tr[%d][%d] = %2d", j, i, r[j][i]);
            j++;
        }
    }
    printf("\n");
    printf("\ncost of Optimal Binary Search Tree: %d\n", c[0][n]);
    printf("\nRoot of Optimal Binary Search Tree: %d\n", r[0][n]);
    printf("\nPreorder Traversal\n");
preorder(r, 0, n, iden);
printf("\n\nInorder Traversal\n");
inorder(r, 0, n, iden);
printf("\n\nPostorder Traversal\n");
postorder(r, 0, n, iden);
}

int main()
{

    int n;
    long long start,end;
    printf("Enter the number of keys\n");
    scanf("%d", &n);
    printf("Enter the keys\n");
    for (int i = 1; i <= n; i++)
    {
        iden[i]=(char*)malloc(MAX*sizeof(char));
        scanf("%s", iden[i]);
    }
    int p[n + 1], q[n + 1];
    printf("Enter the probability of successful search\n");
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    printf("Enter the probability of unsuccessful search\n");
    for (int i = 0; i <= n; i++)
    {
        scanf("%d", &q[i]);
    }
    start=current_time_us();
    OBST(p, q, n);
    end=current_time_us();
    printf("\nTime taken: %lldμs\n", end - start);
    for (int i = 1; i <= n; i++)
    {
        free(iden[i]);
    }
    
    return 0;
}
