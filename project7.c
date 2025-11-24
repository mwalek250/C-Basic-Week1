#include <stdio.h>

int main() {
    int a, b, c; // Declare the variables

    printf("Enter three numbers: ");
    scanf("%d %d %d", &a, &b, &c); // Read input

    if (a >= b && a >= c) {
        printf("The largest number is %d\n", a);
    } else if (b >= a && b >= c) {
        printf("The largest number is %d\n", b);
    } else {
        printf("The largest number is %d\n", c);
    }

    return 0;
}
