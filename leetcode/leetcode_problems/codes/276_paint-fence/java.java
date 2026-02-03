/**
 * Problem: Paint Fence
 * Difficulty: Medium
 * Tags: dp
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int numWays(int n, int k) {
        if (n == 0) return 0;
        if (n == 1) return k;
        if (n == 2) return k * k;
        
        int same = k;
        int diff = k * (k - 1);
        
        for (int i = 3; i <= n; i++) {
            int temp = diff;
            diff = (same + diff) * (k - 1);
            same = temp;
        }
        
        return same + diff;
    }
}