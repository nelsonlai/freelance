/*
 * Problem: Beautiful Arrangement
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>

using namespace std;

class Solution {
private:
    int backtrack(int pos, vector<bool>& used, int n) {
        if (pos > n) {
            return 1;
        }
        
        int count = 0;
        for (int i = 1; i <= n; i++) {
            if (!used[i] && (i % pos == 0 || pos % i == 0)) {
                used[i] = true;
                count += backtrack(pos + 1, used, n);
                used[i] = false;
            }
        }
        
        return count;
    }

public:
    int countArrangement(int n) {
        vector<bool> used(n + 1, false);
        return backtrack(1, used, n);
    }
};