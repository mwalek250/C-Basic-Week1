

#include <stdio.h>

int main() {
    // Declare variables
    int num1, num2;
    int sum, difference, product, quotient;

    // Input two numbers
    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    // Perform arithmetic operations
    sum = num1 + num2;
    difference = num1 - num2;
    product = num1 * num2;

    // Check for division by zero
    if(num2 != 0) {
        quotient = num1 / num2;
    } else {
        printf("Cannot divide by zero.\n");
    }

    // Print results
    printf("Sum = %.2d\n", sum);
    printf("Difference = %.2d\n", difference);
    printf("Product = %.2d\n", product);
    if(num2 != 0) {
        printf("Quotient = %.2d\n", quotient);
    }

    return 0;
}
