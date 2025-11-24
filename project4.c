#include <stdio.h>

int main() {
    float c, f;

    printf("Enter temperature in Celsius: ");
    scanf("%f", &c);
    printf("In Fahrenheit: %.1f\n", (c * 9 / 5) + 32);

    printf("Enter temperature in Fahrenheit: ");
    scanf("%f", &f);
    printf("In Celsius: %.1f\n", (f - 32) * 5 / 9);

    return 0;
}
