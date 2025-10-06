/*
 * week4_1_dynamic_array.c
 * Author: Garvit
 * Student ID: 241ADB140
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Program allocates memory for an integer array, fills it with user data,
 *   computes the sum and average, displays the results, and frees the memory.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    int *arr = NULL;
    int sum = 0;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }
    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input.\n");
            free(arr); // Free memory before exit
            return 1;
        }
        sum += arr[i];
    }
    double avg = (double)sum / n;
    printf("Sum = %d\n", sum);
    printf("Average = %.2f\n", avg);
    free(arr);
    return 0;
}
