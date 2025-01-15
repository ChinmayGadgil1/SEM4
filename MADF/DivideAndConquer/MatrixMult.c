#include <stdio.h>
#include <time.h>

void strassenMatrixMultiply(int A[2][2], int B[2][2], int C[2][2]) {
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

void printMatrix(int matrix[2][2]) {
    printf("Matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%02d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void inputMatrix(int matrix[2][2], char name) {
    printf("Enter elements of matrix %c (2x2):\n", name);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%c[%d][%d]: ", name, i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

int main() {
    int A[2][2], B[2][2], C[2][2];
    int choice;
    clock_t start, end;
    long double cpu_time_used;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Input matrices\n");
        printf("2. Multiply matrices using Strassen's algorithm\n");
        printf("3. Print result matrix\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputMatrix(A, 'A');
                inputMatrix(B, 'B');
                break;
            case 2:
                start = clock();
                strassenMatrixMultiply(A, B, C);
                end = clock();
                cpu_time_used = ((long double) (end - start)) / CLOCKS_PER_SEC;
                printf("Matrix multiplication completed in %lf seconds.\n", cpu_time_used);
                break;
            case 3:
                printf("Result matrix C:\n");
                printMatrix(C);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}