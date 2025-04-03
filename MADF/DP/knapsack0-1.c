#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define MAX 100

long long current_time_us() {
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (counter.QuadPart * 1000000) / freq.QuadPart;  
}

struct Pair
{
    double p; 
    double w; 
} pair[MAX];
int b[MAX];

int maxm(int a, int b)
{
   if(a>b)
        return a;
    return b;
}
int Largest(struct Pair pair[], double w[], int t, int h, int i, int to)
{
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
void TraceBack(double p[], double w[], struct Pair pair[], int x[], int to, int n)
{
    double totalProfit = pair[b[n + 1] - 1].p, weight = pair[b[n + 1] - 1].w; 
    printf("\nprofit=%.2lf    weight=%.2lf\n", totalProfit, pair[b[n + 1] - 1].w);
    double remainingWeight = to;
    for (int i = n - 1; i >= 0; i--)
    {
        int flag = 0;
        for (int j = b[i]; j < b[i + 1]; j++)
        {
            if (pair[j].p == totalProfit)
            {
                x[i] = 0;
                flag = 1;
            }
        }
        if (flag == 0)
        {
            totalProfit = totalProfit - p[i + 1];
            weight = weight - w[i + 1];
            x[i] = 1;
        }
    }
}
void AlgorithmDKnap(double p[], double w[], int x[], int n, int to)
{
    pair[1].p = 0;
    pair[1].w = 0;
    int t = 1;
    int h = 1;
    int next = 2;
    b[0] = 1;
    b[1] = 2;
    for (int i = 1; i <= n; i++)
    {
        int k = t;
        int u = Largest(pair, w, t, h, i, to);
        for (int j = t; j <= u; j++)
        {
            double pp = pair[j].p + p[i];
            double ww = pair[j].w + w[i];
            while (k <= h && pair[k].w < ww)
            {
                pair[next].p = pair[k].p;
                pair[next].w = pair[k].w;
                next++;
                k++;
            }
            if (k <= h && pair[k].w == ww)
            {
                if (pp < pair[k].p)
                {
                    pp = pair[k].p;
                }
                k++;
            }
            if (pp > pair[next - 1].p && ww <= to)
            {
                pair[next].p = pp;
                pair[next].w = ww;
                next++;
            }
            while (k <= h && pair[k].p <= pair[next - 1].p)
                k++;
        }
        while (k <= h)
        {
            pair[next].p = pair[k].p;
            pair[next].w = pair[k].w;
            next++;
            k++;
        }
        t = h + 1;
        h = next - 1;
        b[i + 1] = next;
    }
    TraceBack(p, w, pair, x, to, n);
    printf("\n\n");
    int cnt = 1;
    for (int i = 0; i < n + 1; i++)
    {
        printf(" S%d: ", i);
        for (int j = b[i]; j < b[i + 1]; j++)
        {
            printf(" (%.0lf,%.0lf ) ", pair[cnt].p, pair[cnt].w);
            cnt++;
        }
        printf("\n");
    }

    printf("\n");
}


int main()
{
    double p[MAX]; 
    double w[MAX]; 
    int x[MAX];   
    int n;         
    int to;        
    printf("Enter the number of items: ");
    scanf("%d", &n);
    printf("Enter the profits of items:\n");
    for (int i = 1; i <= n; i++)
    scanf("%lf", &p[i]);
    printf("\n");
    printf("Enter the weights of items:\n");
    for (int i = 1; i <= n; i++)
    scanf("%lf", &w[i]);
    printf("\n");
    printf("Enter capacity: ");
    scanf("%d", &to);
    long long start = current_time_us();
    AlgorithmDKnap(p, w, x, n, to);
    long long end = current_time_us();
    
    printf("\nTime taken: %lldμs\n", end - start);
    printf("\n   ");
    for (int i = 0; i < n; i++)
    {
        printf("[%d]", i + 1);
    }
    printf("\n");
    printf("X :");
    for (int i = 0; i < n; i++)
    {
        printf(" %d ",x[i]);
    }
    printf("\n");
    return 0;
}

