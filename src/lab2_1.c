#include <stdio.h>

/*
    Task:
    Write a function `int sum_to_n(int n)` that computes
    the sum of all integers from 1 up to n using a for loop.

    In main():
      - Ask user for a positive integer n
      - If n < 1, print an error
      - Otherwise, call sum_to_n and print the result
*/

int sum_to_n(int n) {
        //start
    int result = 0;



    for (int i = 1; i <= n; i++) {
        result += i;
        
    }

    return result;
}


int main(void) {
    int n;
    
    
    printf("Enter a positive integer n: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Error\n");
        return 0;
    }
        
    int result = sum_to_n(n);
    printf("Sum = %d\n", result);

    return 0;
}