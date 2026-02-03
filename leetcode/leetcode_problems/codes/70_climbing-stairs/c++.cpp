/*
 * Problem: Climbing Stairs
 * Difficulty: Easy
 * Tags: dp, math
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
public:
    int climbStairs(int n) {
        if (n < 3) {
            return n;
        }
        
        int first = 1, second = 2;
        for (int i = 3; i <= n; i++) {
            int temp = first + second;
            first = second;
            second = temp;
        }
        
        return second;
    }
};