/*
 * Chapter 2 — Algorithm Analysis: General Rules for Loops
 * File: ch2_loop_rules.cpp
 *
 * This program illustrates the standard rules for analyzing running time:
 *   Rule 1: FOR loop — time = (time per iteration) * (number of iterations).
 *   Rule 2: Nested loops — time = product of all loop sizes (for O(1) inner body).
 *   Rule 3: Consecutive statements — add times; the maximum dominates.
 *   Rule 4: If/else — time = test + max(S1, S2).
 */

#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * Fragment 1: Single loop.
 * Runs n times; body is O(1). Total: O(N).
 */
void fragment1(int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        ++sum;
    }
    (void)sum; // avoid unused warning
}

/*
 * Fragment 2: Two nested loops, both 0..n-1.
 * Outer n iterations; inner n iterations per outer → n * n = n^2.
 * Body O(1). Total: O(N^2).
 */
void fragment2(int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ++sum;
        }
    }
    (void)sum;
}

/*
 * Fragment 3: Consecutive blocks — O(N) then O(N^2).
 * Rule 3: Total = O(N) + O(N^2) = O(N^2) (maximum dominates).
 */
void fragment3(int n) {
    int sum = 0;
    // First block: O(N)
    for (int i = 0; i < n; ++i) {
        ++sum;
    }
    // Second block: O(N^2)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ++sum;
        }
    }
    (void)sum;
}

/*
 * Fragment 4: Nested loops, but inner loop depends on outer.
 * Outer i = 0..n-1; inner j = 0..i-1. So inner runs 0 + 1 + 2 + ... + (n-1) = n(n-1)/2.
 * n(n-1)/2 = n^2/2 - n/2 = O(n^2).
 * Total: O(N^2).
 */
void fragment4(int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            ++sum;
        }
    }
    (void)sum;
}

int main(int argc, char* argv[]) {
    int n = argc >= 2 ? atoi(argv[1]) : 100;
    cout << "n = " << n << endl;
    fragment1(n);
    fragment2(n);
    fragment3(n);
    fragment4(n);
    cout << "All fragments run (see comments for Big-Oh)." << endl;
    return 0;
}
