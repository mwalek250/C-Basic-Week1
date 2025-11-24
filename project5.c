#include <stdio.h>

int main() {
    float a, b;
    char op;

    printf("Enter first number: ");
    scanf("%f", &a);

    printf("Enter second number: ");
    scanf("%f", &b);

    printf("Choose operation (+, -, *, /): ");
    scanf(" %c", &op);

    if (op == '+')
        printf("Result = %.2f\n", a + b);
    if (op == '-')
        printf("Result = %.2f\n", a - b);
    if (op == '*')
        printf("Result = %.2f\n", a * b);
    if (op == '/')
        printf("Result = %.2f\n", a / b);

    return 0;
}
