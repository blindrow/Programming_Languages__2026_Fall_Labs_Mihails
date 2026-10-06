/*
 * week4_1_dynamic_array.c
 * Author: [Mihails Semjonovs]
 * Student ID: [251ADB194]
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Allocate memory for n integers, read them from the user,
 *   print their sum and average, and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int number_of_elements;
    int *numbers = NULL;

    printf("Enter number of elements: ");

    if (scanf("%d", &number_of_elements) != 1 || number_of_elements <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    // Create enough space for all entered numbers
    numbers = malloc(number_of_elements * sizeof(int));

    if (numbers == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers: ", number_of_elements);

    int total_sum = 0;

    for (int index = 0; index < number_of_elements; index++) {
        if (scanf("%d", &numbers[index]) != 1) {
            printf("Invalid input.\n");
            free(numbers);
            return 1;
        }

        total_sum += numbers[index];
    }

    // Using double keeps the decimal part of the result
    double average_value =
        (double)total_sum / number_of_elements;

    printf("Sum = %d\n", total_sum);
    printf("Average = %.2f\n", average_value);

    free(numbers);

    return 0;
}