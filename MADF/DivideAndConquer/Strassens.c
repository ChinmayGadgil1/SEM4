#include <stdio.h>
#include <sys/time.h>

long long current_time_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}


void strassenMatrixMultiply(int A[2][2], int B[2][2], int C[2][2])
{
    int P = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
    int Q = (A[1][0] + A[1][1]) * B[0][0];
    int R = A[0][0] * (B[0][1] - B[1][1]);
    int S = A[1][1] * (B[1][0] - B[0][0]);
    int T = (A[0][0] + A[0][1]) * B[1][1];
    int U = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
    int V = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);

    C[0][0] = P + S - T + V;
    C[0][1] = R + T;
    C[1][0] = Q + S;
    C[1][1] = P - Q + R + U;
}

void addMatrix2x2(int A[2][2], int B[2][2], int R[2][2])
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            R[i][j] = A[i][j] + B[i][j];
}

void subtractMatrix2x2(int A[2][2], int B[2][2], int R[2][2])
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            R[i][j] = A[i][j] - B[i][j];
}

void strassenMatrixMultiply4(int A[4][4], int B[4][4], int C[4][4])
{

    int A11[2][2], A12[2][2], A21[2][2], A22[2][2];
    int B11[2][2], B12[2][2], B21[2][2], B22[2][2];

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + 2];
            A21[i][j] = A[i + 2][j];
            A22[i][j] = A[i + 2][j + 2];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + 2];
            B21[i][j] = B[i + 2][j];
            B22[i][j] = B[i + 2][j + 2];
        }
    }

    int temp1[2][2], temp2[2][2];

    addMatrix2x2(A11, A22, temp1);
    addMatrix2x2(B11, B22, temp2);
    int M1[2][2];
    strassenMatrixMultiply(temp1, temp2, M1);

    addMatrix2x2(A21, A22, temp1);
    int M2[2][2];
    strassenMatrixMultiply(temp1, B11, M2);

    subtractMatrix2x2(B12, B22, temp2);
    int M3[2][2];
    strassenMatrixMultiply(A11, temp2, M3);

    subtractMatrix2x2(B21, B11, temp2);
    int M4[2][2];
    strassenMatrixMultiply(A22, temp2, M4);

    addMatrix2x2(A11, A12, temp1);
    int M5[2][2];
    strassenMatrixMultiply(temp1, B22, M5);

    subtractMatrix2x2(A21, A11, temp1);
    addMatrix2x2(B11, B12, temp2);
    int M6[2][2];
    strassenMatrixMultiply(temp1, temp2, M6);

    subtractMatrix2x2(A12, A22, temp1);
    addMatrix2x2(B21, B22, temp2);
    int M7[2][2];
    strassenMatrixMultiply(temp1, temp2, M7);

    int C11[2][2], C12[2][2], C21[2][2], C22[2][2];

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            C11[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            C12[i][j] = M3[i][j] + M5[i][j];
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            C21[i][j] = M2[i][j] + M4[i][j];
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            C22[i][j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + 2] = C12[i][j];
            C[i + 2][j] = C21[i][j];
            C[i + 2][j + 2] = C22[i][j];
        }
    }
}

// Helper function to print a 2x2 matrix.
void printMatrix2x2(int matrix[2][2])
{
    printf("┌     ┐\n");
    for (int i = 0; i < 2; i++)
    {
        printf("│");
        for (int j = 0; j < 2; j++)
        {
            printf(" %4d ", matrix[i][j]);
        }
        printf("│\n");
    }
    printf("└     ┘\n");
}

// Helper function to print a 4x4 matrix.
void printMatrix4(int matrix[4][4])
{
    printf("┌                        ┐\n");
    for (int i = 0; i < 4; i++)
    {
        printf("│");
        for (int j = 0; j < 4; j++)
        {
            printf(" %4d ", matrix[i][j]);
        }
        printf("│\n");
    }
    printf("└                        ┘\n");
}

// Input a 4x4 matrix.
void inputMatrix4(int matrix[4][4], char name)
{
    printf("Enter rows for matrix %c (4x4):\n", name);
    for (int i = 0; i < 4; i++)
    {
        printf("Enter row %d : ", i + 1);
        for (int j = 0; j < 4; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}

int main()
{
    int A[4][4], B[4][4], C[4][4];
    int choice;

    long long start,end;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Input 4x4 matrices\n");
        printf("2. Multiply matrices using Strassen's algorithm (4x4)\n");
        printf("3. Print result matrix\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            inputMatrix4(A, 'A');
            inputMatrix4(B, 'B');
            break;
        case 2:
            start = current_time_us();

            strassenMatrixMultiply4(A, B, C);
             end = current_time_us();
            printf("\nTime taken: %lldμs\n", end - start);

            break;
        case 3:
            printf("Result matrix C:\n");
            printMatrix4(C);
            break;
        case 4:
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}


