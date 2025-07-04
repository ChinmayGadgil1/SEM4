#include <stdio.h>
#define MAX 100

struct Pair {
    double p; 
    double w; 
} pair[MAX];
int b[MAX];

int Largest(struct Pair pair[], int t, int h, int to) {
    int low = t, high = h, ans = t - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (pair[mid].w <= to) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

void TraceBack(double p[], double w[], struct Pair pair[], int x[], int to, int n) {
    double totalProfit = pair[b[n + 1] - 1].p, weight = pair[b[n + 1] - 1].w; 
    printf("Total Profit: %.2lf\n", totalProfit);
    printf("Total Weight: %.2lf\n", weight);

    double remainingWeight = to;
    for (int i = n - 1; i >= 0; i--) {
        int flag = 0;
        for (int j = b[i]; j < b[i + 1]; j++) {
            if (pair[j].p == totalProfit) {
                x[i+1] = 0;
                flag = 1;
            }
        }
        if (flag == 0) {
            totalProfit = totalProfit - p[i + 1];
            weight = weight - w[i + 1];
            x[i+1] = 1;
        }
    }
}

void AlgorithmDKnap(double p[], double w[], int x[], int n, int to) {
    pair[1].p = 0;
    pair[1].w = 0;
    int low = 1;
    int high = 1;
    int next = 2;
    b[0] = 1;
    b[1] = 2;
    
    for (int i = 1; i <= n; i++) {
        int k = low;
        int u = Largest(pair, low, high, to);
        for (int j = low; j <= u; j++) {
            double pp = pair[j].p + p[i];
            double ww = pair[j].w + w[i];
            while (k <= high && pair[k].w < ww) {
                pair[next].p = pair[k].p;
                pair[next].w = pair[k].w;
                next++;
                k++;
            }
            if (k <= high && pair[k].w == ww) {
                if (pp < pair[k].p) {
                    pp = pair[k].p;
                }
                k++;
            }
            if (pp > pair[next - 1].p && ww <= to) {
                pair[next].p = pp;
                pair[next].w = ww;
                next++;
            }
            while (k <= high && pair[k].p <= pair[next - 1].p)
                k++;
        }
        while (k <= high) {
            pair[next].p = pair[k].p;
            pair[next].w = pair[k].w;
            next++;
            k++;
        }
        low = high + 1;
        high = next - 1;
        b[i + 1] = next;
    }
    TraceBack(p, w, pair, x, to, n);
}

int main() {
    double p[MAX], w[MAX]; 
    int x[MAX], n, to;
    
    printf("Enter number of items: ");
    scanf("%d", &n);
    
    printf("Enter profits: ");
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &p[i]);
    }
    
    printf("Enter weights: ");
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &w[i]);
    }
    
    printf("Enter capacity: ");
    scanf("%d", &to);
    
    AlgorithmDKnap(p, w, x, n, to);
    
    printf("Solution vector: ");
    for (int i = 1; i <= n; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");
    
    return 0;
}