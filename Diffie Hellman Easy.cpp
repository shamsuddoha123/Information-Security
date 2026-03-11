#include <cmath>
#include <iostream>

using namespace std;

long long int power(long long int x, long long int y, long long int z)
{
    return ((long long int)pow(x, y)) % z;
}

int main()
{
    long long int p, g;
    long long int a, b;
    long long int A, B;
    long long int Ka, Kb;

    cout << "Enter prime number p: ";
    cin >> p;

    cout << "Enter primitive root g: ";
    cin >> g;

    cout << "Enter Alice private key a: ";
    cin >> a;

    cout << "Enter Bob private key b: ";
    cin >> b;

    A = power(g, a, p);
    B = power(g, b, p);

    cout << "Alice public key (A): " << A << endl;
    cout << "Bob public key (B): " << B << endl;

    Ka = power(B, a, p);
    Kb = power(A, b, p);

    cout << "Shared secret key for Alice: " << Ka << endl;
    cout << "Shared secret key for Bob: " << Kb << endl;
}