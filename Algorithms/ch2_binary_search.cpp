/*
 * Chapter 2 — Logarithms in the Running Time: Binary Search
 * File: ch2_binary_search.cpp
 *
 * Binary Search: Given a SORTED array A[0..N-1] and a value X, find an index i
 * such that A[i] == X, or return -1 if X is not in the array.
 *
 * Why O(log N)?
 *   - Each comparison eliminates half of the remaining range.
 *   - After k steps, the range has size at most N / 2^k.
 *   - When N / 2^k < 1 we are done, so k is about log2(N).
 *   - Thus the number of iterations is O(log N); each iteration is O(1).
 *
 * Assumption: The input is already in memory (reading N elements would be Omega(N)).
 * Binary search is useful when the data are static (no insertions/deletions) and
 * we need many lookups — e.g., periodic table of elements (~118 elements => at most 8 accesses).
 */

#include <iostream>
#include <vector>

using namespace std;

const int NOT_FOUND = -1;

/*
 * Performs standard binary search with two comparisons per level.
 * Returns index where item is found, or NOT_FOUND (-1) if not found.
 * Running time: O(log N).
 */
template <typename Comparable>
int binarySearch(const vector<Comparable>& a, const Comparable& x) {
    int low  = 0;
    int high = (int)a.size() - 1;

    // Each iteration halves the range [low, high]
    while (low <= high) {
        // Midpoint (avoid overflow: use low + (high - low) / 2 for very large arrays)
        int mid = (low + high) / 2;

        if (a[mid] < x) {
            // X must be in the right half (if present)
            low = mid + 1;
        } else if (a[mid] > x) {
            // X must be in the left half (if present)
            high = mid - 1;
        } else {
            // Found
            return mid;
        }
    }
    return NOT_FOUND;
}

/*
 * Recursive version of binary search (same O(log N) time, but uses O(log N) stack space).
 * Included for teaching: recursion that cuts problem size in half => O(log N) depth.
 */
template <typename Comparable>
int binarySearchRec(const vector<Comparable>& a, const Comparable& x, int low, int high) {
    if (low > high) {
        return NOT_FOUND;
    }
    int mid = (low + high) / 2;
    if (a[mid] < x) {
        return binarySearchRec(a, x, mid + 1, high);
    } else if (a[mid] > x) {
        return binarySearchRec(a, x, low, mid - 1);
    } else {
        return mid;
    }
}

int main() {
    vector<int> a = { 2, 5, 8, 11, 14, 17, 20, 23, 26, 29 };

    cout << "Sorted array: ";
    for (int x : a) cout << x << " ";
    cout << endl;

    int x = 11;
    int idx = binarySearch(a, x);
    cout << "binarySearch(a, " << x << ") = " << idx << (idx >= 0 ? " (found)" : " (not found)") << endl;

    x = 7;
    idx = binarySearch(a, x);
    cout << "binarySearch(a, " << x << ") = " << idx << (idx >= 0 ? " (found)" : " (not found)") << endl;

    return 0;
}
