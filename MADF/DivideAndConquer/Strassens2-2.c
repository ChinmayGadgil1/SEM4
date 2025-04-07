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

void printMatrix2x2(int matrix[2][2])
{
    printf("┌            ┐\n");
    for (int i = 0; i < 2; i++)
    {
        printf("│");
        for (int j = 0; j < 2; j++)
        {
            printf(" %4d ", matrix[i][j]);
        }
        printf("│\n");
    }
    printf("└            ┘\n");
}

void inputMatrix2x2(int matrix[2][2], char name)
{
    printf("Enter rows for matrix %c (2x2):\n", name);
    for (int i = 0; i < 2; i++)
    {
        printf("Enter row %d : ", i + 1);
        for (int j = 0; j < 2; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}

int main()
{
    int A[2][2], B[2][2], C[2][2];
    int choice;
    long long start, end;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Input 2x2 matrices\n");
        printf("2. Multiply matrices using Strassen's algorithm (2x2)\n");
        printf("3. Print result matrix\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            inputMatrix2x2(A, 'A');
            inputMatrix2x2(B, 'B');
            break;
        case 2:
            start = current_time_us();
            strassenMatrixMultiply(A, B, C);
            end = current_time_us();
            printf("\nTime taken: %lldμs\n", end - start);
            break;
        case 3:
            printf("Result matrix C:\n");
            printMatrix2x2(C);
            break;
        case 4:
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
