/*
 * Problem: Count Numbers with Unique Digits
 * Difficulty: Medium
 * Tags: dp, math
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) {
            return 1;
        }
        
        int result = 10;
        int available = 9;
        
        for (int i = 2; i <= n; i++) {
            available *= (10 - i + 1);
            result += available;
        }
        
        return result;
    }
};