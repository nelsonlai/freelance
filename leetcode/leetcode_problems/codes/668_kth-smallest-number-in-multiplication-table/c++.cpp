/*
 * Problem: Kth Smallest Number in Multiplication Table
 * Difficulty: Hard
 * Tags: math, search
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <algorithm>

using namespace std;

class Solution {
private:
    int countLessEqual(int m, int n, int x) {
        int count = 0;
        for (int i = 1; i <= m; i++) {
            count += min(x / i, n);
        }
        return count;
    }

public:
    int findKthNumber(int m, int n, int k) {
        int left = 1, right = m * n;
        
        while (left < right) {
            int mid = (left + right) / 2;
            if (countLessEqual(m, n, mid) < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
};