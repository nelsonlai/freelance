/*
 * Problem: Detect Pattern of Length M Repeated K or More Times
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    bool containsPattern(vector<int>& arr, int m, int k) {
        int n = arr.size();
        for (int i = 0; i <= n - m * k; i++) {
            bool valid = true;
            for (int j = 1; j < k; j++) {
                for (int p = 0; p < m; p++) {
                    if (arr[i + p] != arr[i + j * m + p]) {
                        valid = false;
                        break;
                    }
                }
                if (!valid) {
                    break;
                }
            }
            if (valid) {
                return true;
            }
        }
        return false;
    }
};