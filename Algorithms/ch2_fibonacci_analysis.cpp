/*
 * Chapter 2 — Running-Time Analysis: Recursion Gone Wrong vs Right
 * File: ch2_fibonacci_analysis.cpp
 *
 * Fibonacci: F(0)=1, F(1)=1, F(n)=F(n-1)+F(n-2) for n>=2.
 * (Some definitions use F(0)=0; the analysis is the same.)
 *
 * NAIVE RECURSIVE VERSION:
 *   - T(n) = T(n-1) + T(n-2) + O(1).
 *   - It can be shown T(n) >= F(n). And F(n) grows like phi^n where phi = (1+sqrt(5))/2.
 *   - So the naive recursive algorithm is EXPONENTIAL: O(phi^n) — useless for n > 40.
 *   - Why? The same subproblems (e.g., F(n-2)) are computed many times (compound redundancy).
 *
 * ITERATIVE (DYNAMIC PROGRAMMING) VERSION:
 *   - Compute F(0), F(1), ..., F(n) in order, each in O(1) time using the previous two.
 *   - Running time: O(N). Space: O(1) if we only keep last two values.
 *
 * This illustrates: "Don't compute anything more than once" and the danger of
 * naive recursion when subproblems overlap.
 */

#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * Naive recursive Fibonacci.
 * Running time: T(n) = T(n-1) + T(n-2) + O(1) => T(n) = O(phi^n), i.e., EXPONENTIAL.
 * Do NOT use for n larger than about 40.
 */
long long fibRecursive(int n) {
    if (n <= 1) {
        return 1;
    }
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

/*
 * Iterative Fibonacci using two variables (current and previous).
 * Running time: O(N). Space: O(1).
 */
long long fibIterative(int n) {
    if (n <= 1) {
        return 1;
    }
    long long prev = 1, curr = 1;
    for (int i = 2; i <= n; ++i) {
        long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

/*
 * Alternative: iterative with array (useful if we need all F(0)..F(n)).
 * Running time: O(N). Space: O(N).
 */
long long fibArray(int n) {
    if (n <= 1) return 1;
    long long* f = new long long[n + 1];
    f[0] = f[1] = 1;
    for (int i = 2; i <= n; ++i) {
        f[i] = f[i - 1] + f[i - 2];
    }
    long long result = f[n];
    delete[] f;
    return result;
}

int main(int argc, char* argv[]) {
    int n = 10;
    if (argc >= 2) {
        n = atoi(argv[1]);
    }

    cout << "Fibonacci F(0)=1, F(1)=1, F(n)=F(n-1)+F(n-2)" << endl;
    cout << "n = " << n << endl;

    // For small n we can use recursive; for larger n it becomes very slow
    if (n <= 40) {
        cout << "fibRecursive(" << n << ") = " << fibRecursive(n) << "  [O(phi^n) - slow for large n]" << endl;
    } else {
        cout << "(Skipping recursive for n > 40 to avoid long wait.)" << endl;
    }

    cout << "fibIterative(" << n << ") = " << fibIterative(n) << "  [O(N)]" << endl;
    cout << "fibArray("     << n << ") = " << fibArray(n)     << "  [O(N)]" << endl;

    return 0;
}
