/**
 * Problem: Maximum Number of Coins You Can Get
 * Difficulty: Medium
 * Tags: array, greedy, math, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int maxCoins(int[] piles) {
        Arrays.sort(piles);
        int n = piles.length;
        int result = 0;
        
        for (int i = n / 3; i < n; i += 2) {
            result += piles[i];
        }
        
        return result;
    }
}