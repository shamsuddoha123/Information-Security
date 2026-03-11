#include <stdio.h>

int main() {
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    int r1 = a, r2 = b;
    int s1 = 1, s2 = 0;
    int t1 = 0, t2 = 1;

    while (r2 != 0) {
        int q = r1 / r2;

        int r = r1 - q * r2;
        r1 = r2;
        r2 = r;

        int s = s1 - q * s2;
        s1 = s2;
        s2 = s;

        int t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }

    printf("GCD of %d and %d is %d\n", a, b, r1);
    printf("Coefficients: x = %d, y = %d\n", s1, t1);
    printf("Check: %d*%d + %d*%d = %d\n", a, s1, b, t1, r1);

    return 0;
}
