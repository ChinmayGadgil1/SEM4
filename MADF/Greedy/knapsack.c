#include <stdio.h>
#define MAX 100

double P[MAX];
double W[MAX];
double P_per_W[MAX];
double X[MAX];

void sort(double* arr, double* w, double* p, int n) {
    for (int i = 0; i < n - 1; i++) {
        int flag = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                double tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                
                tmp = w[j];
                w[j] = w[j + 1];
                w[j + 1] = tmp;
                
                tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
                
                flag = 1;
            }
        }
        if (flag == 0) {
            break;
        }
    }
}

void Knapsack(int m, int n) {
    for (int i = 0; i < n; i++) {
        X[i] = 0;
    }
    int u = m, i;
    for (i = 0; i < n; i++) {
        if (W[i] > u) break;
        X[i] = 1.0;
        u -= W[i];
    }
    if (i < n) {
        X[i] = (double)u / W[i];
    }
}

int main() {
    int m = 30, n = 10;
    double x[] = {5, 5, 4, 2, 5, 6, 3, 4, 8, 2};
    double y[] = {23, 13, 26, 34, 11, 26, 31, 19, 19, 26};

    for (int i = 0; i < n; i++) {
        W[i] = x[i];
        P[i] = y[i];
    }

    

    for (int i = 0; i < n; i++) {
        P_per_W[i] = P[i] / W[i];
    }

    sort(P_per_W, W, P, n);

    printf("\n");

    Knapsack(m, n);

    double max_prof = 0;
    double w = 0;
    for (int i = 0; i < n; i++) {
        printf("%.2f ", X[i]);
        max_prof += X[i] * P[i];
        w += (X[i] * W[i]);
    }
    printf("\n");
    printf("%.2f    %.2f\n", w, max_prof);

    return 0;
}