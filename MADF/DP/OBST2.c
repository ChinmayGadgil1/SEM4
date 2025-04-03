#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

int w[MAX][MAX];
int c[MAX][MAX];
int r[MAX][MAX];

char* iden[MAX];

// Structure for tree node
typedef struct TreeNode {
    char* key;
    int index;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

long long current_time_us(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

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
void printLevel(TreeNode* root, int level)
{
    if (root == NULL)
    {
        // Print placeholder for empty nodes to maintain structure
        if (level == 1)
            printf("NULL  ");
        return;
    }
    
    if (level == 1)
        printf("%s(k=%d)  ", root->key, root->index);
    else if (level > 1)
    {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
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

// Function to construct tree from r matrix
TreeNode* constructTree(int r[MAX][MAX], int i, int j, char *identifiers[])
{
    if (i >= j || r[i][j] == 0)
        return NULL;
        
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->key = identifiers[r[i][j]];
    node->index = r[i][j];
    node->left = constructTree(r, i, r[i][j] - 1, identifiers);
    node->right = constructTree(r, r[i][j], j, identifiers);
    
    return node;
}

// Function to get height of the tree
int getHeight(TreeNode* root)
{
    if (root == NULL)
        return 0;
    
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// Function to print tree level by level
void printLevelOrder(TreeNode* root)
{
    if (root == NULL)
        return;
    
    // Get height of tree
    int h = getHeight(root);
    
    // Print tree level by level
    for (int i = 1; i <= h; i++)
    {
        printf("\nLevel %d: ", i);
        printLevel(root, i);
        printf("\n");
    }
}

// Function to print nodes at a specific level

void fillTree(char*** tree, TreeNode* root, int level, int start, int end)
{
    if (root == NULL)
        return;
        
    int mid = (start + end) / 2;
    
    // Allocate memory and store the node value
    char buffer[50];
    sprintf(buffer, "%s(%d)", root->key, root->index);
    tree[level][mid] = strdup(buffer);
    
    // Recursively fill left and right subtrees
    fillTree(tree, root->left, level + 1, start, mid - 1);
    fillTree(tree, root->right, level + 1, mid + 1, end);
}

// Function to print tree graphically
void printTree(TreeNode* root)
{
    if (root == NULL)
        return;
        
    int height = getHeight(root);
    int width = (1 << height) - 1;
    
    // Create a 2D array to store the tree
    char*** tree = (char***)malloc(height * sizeof(char**));
    for (int i = 0; i < height; i++)
    {
        tree[i] = (char**)malloc(width * sizeof(char*));
        for (int j = 0; j < width; j++)
            tree[i][j] = NULL;
    }
    
    // Fill the 2D array with tree elements
    fillTree(tree, root, 0, 0, width - 1);
    
    // Print the tree
    printf("\n\nVisual Representation of OBST:\n");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (tree[i][j] != NULL)
                printf("%s ", tree[i][j]);
            else
                printf("    ");
        }
        printf("\n");
    }
    
    // Free the 2D array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            if (tree[i][j] != NULL)
                free(tree[i][j]);
        free(tree[i]);
    }
    free(tree);
}

// Helper function to fill the 2D array

// Free the tree memory
void freeTree(TreeNode* root)
{
    if (root == NULL)
        return;
    
    freeTree(root->left);
    freeTree(root->right);
    free(root);
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
    printf("\nCost of Optimal Binary Search Tree: %d\n", c[0][n]);
    printf("\nRoot of Optimal Binary Search Tree: %d\n", r[0][n]);
    printf("\nPreorder Traversal\n");
    preorder(r, 0, n, iden);
    printf("\n\nInorder Traversal\n");
    inorder(r, 0, n, iden);
    printf("\n\nPostorder Traversal\n");
    postorder(r, 0, n, iden);
    
    // Construct and display the tree
    TreeNode* root = constructTree(r, 0, n, iden);
    printf("\n\nLevel-Order Tree Display:\n");
    printLevelOrder(root);
    
    // Print tree graphically
    printTree(root);
    
    // Free the tree
    freeTree(root);
}


int main()
{
    int n;
    long long start, end;
    printf("Enter the number of keys\n");
    scanf("%d", &n);
    printf("Enter the keys\n");
    for (int i = 1; i <= n; i++)
    {
        iden[i] = (char*)malloc(MAX*sizeof(char));
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
    
    start = current_time_us();
    OBST(p, q, n);
    end = current_time_us();
    
    printf("\nTime taken: %lldμs\n", end - start);
    
    for (int i = 1; i <= n; i++)
    {
        free(iden[i]);
    }
    
    return 0;
}