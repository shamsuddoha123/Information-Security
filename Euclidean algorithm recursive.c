#include <stdio.h>

// Recursive Euclidean Algorithm
int gcd(int a, int b) {
    if (b == 0)
        return a;   // base case
    return gcd(b, a % b);  // recursive step
}

int main() {
    int num1, num2;

    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);

    printf("GCD of %d and %d is: %d\n", num1, num2, gcd(num1, num2));

    return 0;
}
