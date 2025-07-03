# include<stdio.h>
#define MAX 100
struct item
{
    float p;
    float w;
    int initial_pos;
    float prof_per_w;
    float x;
    float y;
} arr[MAX], tmp[MAX];
int m, n;
float fp=0,fw=0;

int sort_method = 0;
void merge(int low, int mid, int high)
{
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high)
    {
        if (sort_method == 0)
        {
            if (arr[i].prof_per_w >= arr[j].prof_per_w)
            {
                tmp[k] = arr[i];
                i++;
            }
            else
            {
                tmp[k] = arr[j];
                j++;
            }
        }
        else
        {
            if (arr[i].initial_pos < arr[j].initial_pos)
            {
                tmp[k] = arr[i];
                i++;
            }
            else
            {
                tmp[k] = arr[j];
                j++;
            }
        }
        k++;
    }
    if (i <= mid)
    {
        for (int x = i; x <= mid; x++)
        {
            tmp[k] = arr[x];
            k++;
        }
    }
    else if (j <= high)
    {
        for (int x = j; x <= high; x++)
        {
            tmp[k] = arr[x];
            k++;
        }
    }
    for (int i = low; i <= high; i++)
    {
        arr[i] = tmp[i];
    }
}

void mergesort(int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergesort(low, mid);
        mergesort(mid + 1, high);
        merge(low, mid, high);
    }
}

float Bound(float cp,float cw, int k){
    float b=cp;
    float c=cw;
    for(int i=k+1;i<=n;i++){
        c+=arr[i].w;
        if(c<m) b+=arr[i].p;
        else{
            return b+(1.0-(c-m)/arr[i].w)*arr[i].p;
        }        
    }
    return b;
}

void BKnap(int k,float cp,float cw){
    if(cw+arr[k].w<=m){
        arr[k].y=1;
        if(k<n){
            BKnap(k+1,cp+arr[k].p,cw+arr[k].w);
        }
        if((cp+arr[k].p>fp) && k==n){
            fp=cp+arr[k].p;
            fw=cw+arr[k].w;
            for(int j=1;j<=k;j++){
                arr[j].x=arr[j].y;
            }
        }

    }

    if(Bound(cp,cw,k)>=fp){
        arr[k].y=0;
        if(k<n){
            BKnap(k+1,cp,cw);
        }
        if(cp>fp && k==n){
            fp=cp;
            fw=cw;
            for(int j=1;j<=k;j++){
                arr[j].x=arr[j].y;
            }
        }
    }

}


int main()
{

    printf("Enter knapsack capacity: ");
    scanf("%d", &m);
    printf("Enter number of arr: ");
    scanf("%d", &n);
    printf("Enter ws: ");
    for (int i = 1; i <= n; i++)
    {
        scanf("%f", &arr[i].w);
    }

    printf("Enter ps: ");
    for (int i = 1; i <= n; i++)
    {
        scanf("%f", &arr[i].p);
    }
    for (int i = 1; i <= n; i++)
    {
        arr[i].prof_per_w = (float)arr[i].p / arr[i].w;
        arr[i].initial_pos = i;
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%f ", arr[i].prof_per_w);
    }
    printf("\n");
    mergesort(1, n);
    printf("\n");
    BKnap(1,0,0);
    sort_method = 1;
    mergesort(1, n);
    for(int i=1;i<=n;i++){
        printf("%.1f ", arr[i].x);
    }
    printf("\n");

    return 0;
}