/*
 * Chapter 2 — Logarithms in the Running Time: GCD and Exponentiation
 * File: ch2_gcd_exponentiation.cpp
 *
 * Two classic O(log N) algorithms:
 *   1. Euclid's algorithm for greatest common divisor (gcd).
 *   2. Efficient exponentiation: compute X^N with O(log N) multiplications.
 *
 * GCD: gcd(M, N) = largest integer that divides both M and N.
 *      Example: gcd(50, 15) = 5.
 *      Theorem: After two iterations of Euclid's algorithm, the remainder is at most
 *      half of its previous value => number of iterations is O(log N).
 *
 * Exponentiation: Naive algorithm uses N-1 multiplications => O(N).
 *      We use: X^N = (X^(N/2))^2 if N is even, and X^N = (X^((N-1)/2))^2 * X if N is odd.
 *      At most 2 multiplications per halving => O(log N) multiplications.
 */

#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * Euclid's algorithm: gcd(m, n) where we assume m >= n (if not, first iteration swaps).
 * Repeatedly replace (m, n) by (n, m % n) until n == 0; then gcd is m.
 * Running time: O(log(min(m,n))). In practice, very fast.
 */
long long gcd(long long m, long long n) {
    while (n != 0) {
        long long rem = m % n;
        m = n;
        n = rem;
    }
    return m;
}

/* Helper: check if n is even */
static bool isEven(int n) {
    return (n % 2) == 0;
}

/*
 * Efficient exponentiation: compute x^n with O(log n) multiplications.
 * Base: x^0 = 1, x^1 = 1.
 * If n is even: x^n = (x^2)^(n/2).
 * If n is odd:  x^n = (x^2)^(n/2) * x.
 * Each step halves n => at most 2*log2(n) multiplications.
 *
 * WARNING: For large n, x^n can overflow; this is for teaching the algorithm.
 */
long long pow(long long x, int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return x;
    }
    if (isEven(n)) {
        return pow(x * x, n / 2);
    } else {
        return pow(x * x, n / 2) * x;
    }
}

/*
 * Iterative (non-recursive) version of fast exponentiation.
 * Same O(log N) multiplications; avoids recursion stack.
 */
long long powIterative(long long x, int n) {
    long long result = 1;
    long long base   = x;
    int exp = n;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

int main(int argc, char* argv[]) {
    // GCD examples
    cout << "Euclid's GCD:" << endl;
    cout << "  gcd(50, 15) = "   << gcd(50, 15)   << endl;
    cout << "  gcd(1989, 1590) = " << gcd(1989, 1590) << endl;

    // Exponentiation examples
    cout << "\nEfficient exponentiation (x^n):" << endl;
    int x = 2, n = 10;
    if (argc >= 3) {
        x = atoi(argv[1]);
        n = atoi(argv[2]);
    }
    cout << "  pow(" << x << ", " << n << ") = " << pow(x, n) << endl;
    cout << "  powIterative(" << x << ", " << n << ") = " << powIterative(x, n) << endl;

    return 0;
}
