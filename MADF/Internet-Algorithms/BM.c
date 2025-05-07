#include <stdio.h>
#include <string.h>
#define MAX 100
#include <sys/time.h>

char p[MAX];
char t[MAX];
int cmp[MAX] = {0};
int comparison_count = 0; 
int store;
int lastoccurrence(char a) {
    int m = strlen(p);
    for (int i = m - 1; i >= 0; i--) {
        if (p[i] == a) {
            return i;
        }
    }
    return -1;
}

long long current_time_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}


int min(int a, int b) {
    return (a <= b) ? a : b;
}

void print_text() {
    int n = strlen(t);

    printf("Pattern: %s\n", p);
    
    printf("    ");  
    for (int i = 0; i < n; i++) {
        printf("%4d", i); 
    }
    printf("\n");
    
    printf("    ");  
    for (int i = 0; i < n; i++) {
        printf("----"); 
    }
    printf("\n");
    
    printf("    ");  
    for (int i = 0; i < n; i++) {
        printf("|%3c", t[i]);  
    }
    printf("|\n");
    
    printf("    ");  
    for (int i = 0; i < n; i++) {
        printf("----"); 
    }
    printf("\n");
}

void print_pattern(int i, int j, int lastocc) {
    int m = strlen(p);
    int n = strlen(t);
    
    printf("\n");
    for (int k = 0; k < (i - j + 1); k++) {
        printf("    ");  
    }
    
    for (int idx = 0; idx < m; idx++) {
        printf("|%3c", p[idx]);  
    }
    printf("| i = %d lastocc = %d\n", i, lastocc);

    for (int k = 0; k < (i - j + 1); k++) {
        printf("    ");  
    }
   
    for (int idx = 0; idx < m; idx++) {
        printf("|%3d", cmp[idx]); 
    }
    printf("| j = %d\n", j);
}

int BM() {
    print_text();
    int m = strlen(p);
    int n = strlen(t);
    int i = m - 1;
    int j = m - 1;
    int flag = 1;

    do {
        comparison_count++; 
        if (p[j] == t[i]) {
            cmp[j]++;
            if (j == 0) {
                return i;
            } else {
                i--;
                j--;
            }
        } else {
            cmp[j]++;
            int lastocc = lastoccurrence(t[i]);
            store = n - i - (m - j);
            print_pattern( i, j, lastocc);
            i = i + m - min(j, lastocc + 1);
            j = m - 1;
        }
    } while (i <= n - 1);
    return -1;
}


int main() {
    int choice;
    long long start_time, end_time;
    do {
        printf("\nBoyer-Moore Pattern Matching Algorithm\n");
        printf("1. Enter new text and pattern\n");
        printf("2. Search pattern\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch(choice) {
            case 1:
                printf("Enter the text: ");
                fgets(t, MAX, stdin);
                t[strcspn(t, "\n")] = 0;

                printf("Enter the pattern to search: ");
                fgets(p, MAX, stdin);
                p[strcspn(p, "\n")] = 0; 
                break;

            case 2:
                if (strlen(t) == 0 || strlen(p) == 0) {
                    printf("Please enter text and pattern first!\n");
                    break;
                }
                comparison_count = 0;
                memset(cmp, 0, sizeof(cmp)); 
                
                printf("\nText: %s\n", t);
                printf("Pattern: %s\n", p);
                start_time = current_time_us();
                
                int i = BM();
                print_pattern( i, 0, 0);
                end_time = current_time_us();
                printf("Time taken: %lld μs\n", end_time - start_time);
                if (i != -1) {
                    printf("\nPattern found at index: %d\n", i);
                } else {
                    printf("\nPattern not found in the text\n");
                }
                printf("Number of comparisons made: %d\n", comparison_count);
                break;

            case 3:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
