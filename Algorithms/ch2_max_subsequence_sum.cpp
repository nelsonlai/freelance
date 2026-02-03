/*
 * Chapter 2 — Maximum Subsequence Sum Problem
 * File: ch2_max_subsequence_sum.cpp
 *
 * Problem: Given (possibly negative) integers A[0..N-1], find the maximum value of
 *   sum = A[i] + A[i+1] + ... + A[j]  for any i <= j.
 * If all integers are negative, the maximum subsequence sum is defined to be 0.
 *
 * Example: For -2, 11, -4, 13, -5, -2 the answer is 20 (elements 11, -4, 13).
 *
 * This file implements four algorithms with running times:
 *   Algorithm 1: O(N^3) — exhaustive (three nested loops)
 *   Algorithm 2: O(N^2) — improve by reusing prefix sums
 *   Algorithm 3: O(N log N) — divide and conquer
 *   Algorithm 4: O(N) — single pass (online, constant space) - Kadane's algorithm
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
 * Algorithm 1: Cubic — try every pair (i, j) and sum A[i..j].
 * Three nested loops: i = start, j = end, k = index to sum.
 * Running time: O(N^3). Space: O(1).
 */
int maxSubSum1(const vector<int>& a) {
    int maxSum = 0;
    int n = (int)a.size();

    // For each possible start index i
    for (int i = 0; i < n; ++i) {
        // For each possible end index j >= i
        for (int j = i; j < n; ++j) {
            int thisSum = 0;
            // Sum A[i] through A[j] — this inner loop makes it O(N^3)
            for (int k = i; k <= j; ++k) {
                thisSum += a[k];
            }
            if (thisSum > maxSum) {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

/*
 * Algorithm 2: Quadratic — for each start i, extend j and maintain running sum.
 * Key: sum(A[i..j]) = sum(A[i..j-1]) + A[j], so we don't need the innermost loop.
 * Running time: O(N^2). Space: O(1).
 */
int maxSubSum2(const vector<int>& a) {
    int maxSum = 0;
    int n = (int)a.size();

    for (int i = 0; i < n; ++i) {
        int thisSum = 0;
        // Extend the subsequence ending at j; add A[j] to thisSum
        for (int j = i; j < n; ++j) {
            thisSum += a[j];
            if (thisSum > maxSum) {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

/*
 * Helper: returns the maximum of three integers.
 * Used in the divide-and-conquer algorithm.
 */
static int max3(int a, int b, int c) {
    return max(a, max(b, c));
}

/*
 * Algorithm 3: Divide and Conquer — O(N log N).
 * The maximum sum is either:
 *   (1) entirely in the left half,
 *   (2) entirely in the right half, or
 *   (3) spans the middle (max suffix of left + max prefix of right).
 * We solve (1) and (2) recursively, and (3) by two linear scans from center.
 * Recurrence: T(N) = 2*T(N/2) + O(N) => T(N) = O(N log N).
 */
int maxSumRec(const vector<int>& a, int left, int right) {
    // Base case: one element
    if (left == right) {
        return a[left] > 0 ? a[left] : 0;
    }

    int center = (left + right) / 2;

    // Recursively solve left and right halves
    int maxLeftSum  = maxSumRec(a, left, center);
    int maxRightSum = maxSumRec(a, center + 1, right);

    // Max sum that touches the center from the left (suffix of left half)
    int maxLeftBorderSum = 0, leftBorderSum = 0;
    for (int i = center; i >= left; --i) {
        leftBorderSum += a[i];
        if (leftBorderSum > maxLeftBorderSum) {
            maxLeftBorderSum = leftBorderSum;
        }
    }

    // Max sum that touches the center from the right (prefix of right half)
    int maxRightBorderSum = 0, rightBorderSum = 0;
    for (int j = center + 1; j <= right; ++j) {
        rightBorderSum += a[j];
        if (rightBorderSum > maxRightBorderSum) {
            maxRightBorderSum = rightBorderSum;
        }
    }

    // Best is max of: left-only, right-only, or crossing middle
    return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

int maxSubSum3(const vector<int>& a) {
    if (a.empty()) return 0;
    return maxSumRec(a, 0, (int)a.size() - 1);
}

/*
 * Algorithm 4: Linear — single pass (Kadane-style).
 * Observation: If the sum from index i to j is negative, we never want to
 * start a subsequence at any index in [i, j]; we can advance the "start" to j+1.
 * So we maintain: thisSum = best sum ending at current j; reset to 0 if negative.
 * Running time: O(N). Space: O(1). Online: can process stream without storing all data.
 */
int maxSubSum4(const vector<int>& a) {
    int maxSum = 0, thisSum = 0;

    for (size_t j = 0; j < a.size(); ++j) {
        thisSum += a[j];
        if (thisSum > maxSum) {
            maxSum = thisSum;
        } else if (thisSum < 0) {
            // Any subsequence starting earlier up to j has non-positive sum; reset
            thisSum = 0;
        }
    }
    return maxSum;
}

int main() {
    // Example from the text: -2, 11, -4, 13, -5, -2 => 20
    vector<int> a = { -2, 11, -4, 13, -5, -2 };

    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << endl;

    cout << "Max subsequence sum (Alg1 O(N^3)):  " << maxSubSum1(a) << endl;
    cout << "Max subsequence sum (Alg2 O(N^2)):  " << maxSubSum2(a) << endl;
    cout << "Max subsequence sum (Alg3 O(N log N)): " << maxSubSum3(a) << endl;
    cout << "Max subsequence sum (Alg4 O(N)):    " << maxSubSum4(a) << endl; // Kadane's algorithm

    return 0;
}
