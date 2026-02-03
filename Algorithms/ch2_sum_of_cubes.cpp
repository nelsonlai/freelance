/*
 * Chapter 2 — Algorithm Analysis: A Simple Example
 * File: ch2_sum_of_cubes.cpp
 *
 * This program demonstrates basic running-time analysis (Big-Oh) on a simple
 * loop. We compute the sum of cubes: sum = 1^3 + 2^3 + ... + n^3
 *
 * ANALYSIS:
 *   - Line "partialSum = 0" and "return partialSum" are O(1).
 *   - The for loop runs exactly n times.
 *   - Each iteration does a constant amount of work (multiplications, addition, assignment).
 *   - Total time: O(1) + n * O(1) + O(1) = O(n).
 *
 * We ignore constants (e.g., 6n + 4) and report O(N).
 */

#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * Computes 1^3 + 2^3 + ... + n^3.
 * Running time: O(N).
 */
int sumOfCubes(int n) {
    // O(1): declaration and initialization
    int partialSum = 0;

    // Loop runs n times. Each iteration is O(1).
    // So the loop is O(n) total.
    for (int i = 1; i <= n; ++i) {
        // Three multiplications (i*i*i), one addition, one assignment = O(1)
        partialSum += i * i * i;
    }

    // O(1): return
    return partialSum;
}

/*
 * Optional: closed-form formula for sum of cubes.
 * Sum of cubes = (1 + 2 + ... + n)^2 = (n(n+1)/2)^2
 * This is O(1) if we assume arithmetic is constant time (as in our model).
 */
long long sumOfCubesFormula(int n) {
    long long s = (long long)n * (n + 1) / 2;
    return s * s;
}

int main(int argc, char* argv[]) {
    // Default n for demonstration
    int n = 10;
    if (argc >= 2) {
        n = atoi(argv[1]);
    }

    cout << "Sum of cubes 1^3 + ... + " << n << "^3 (loop):    " << sumOfCubes(n) << endl;
    cout << "Sum of cubes 1^3 + ... + " << n << "^3 (formula): " << sumOfCubesFormula(n) << endl;

    return 0;
}
