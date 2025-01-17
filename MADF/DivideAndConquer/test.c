#include <stdio.h>

int main() {
    int size;

    // Ask the user for the size of the triangle
    printf("Enter the size of the triangle: ");
    scanf("%d", &size);

    // Loop through each row of the triangle
    for (int i = 1; i <= size; i++) {
        // Print leading spaces
        for (int j = 0; j < size - i; j++)
            printf(" ");

        // Print asterisks
        for (int k = 0; k < i; k++)
            printf("* ");
        
        // Move to a new line after each row
        printf("\n");
    }

    return 0;
}