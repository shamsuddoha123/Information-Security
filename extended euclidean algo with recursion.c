#include <stdio.h>

// Recursive function returning gcd and computing x, y
void extended_gcd(int r1, int r2, int s1, int s2, int t1, int t2, int *gcd, int *x, int *y) {
    if (r2 == 0) {
        *gcd = r1;
        *x = s1;
        *y = t1;
        return;
    }

    int q = r1 / r2;

    // Recurse with updated values
    extended_gcd(r2, r1 - q * r2,
                 s2, s1 - q * s2,
                 t2, t1 - q * t2,
                 gcd, x, y);
}

int main() {
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    int gcd, x, y;
    extended_gcd(a, b, 1, 0, 0, 1, &gcd, &x, &y);

    printf("GCD of %d and %d is %d\n", a, b, gcd);
    printf("Coefficients: x = %d, y = %d\n", x, y);
    printf("Check: %d*%d + %d*%d = %d\n", a, x, b, y, gcd);

    return 0;
}
