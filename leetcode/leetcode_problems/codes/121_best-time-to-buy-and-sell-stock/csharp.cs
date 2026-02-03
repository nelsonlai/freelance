/*
 * Problem: Best Time to Buy and Sell Stock
 * Difficulty: Easy
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

public class Solution {
    public int MaxProfit(int[] prices) {
        if (prices.Length == 0) {
            return 0;
        }
        
        int minPrice = prices[0];
        int maxProfit = 0;
        
        for (int i = 1; i < prices.Length; i++) {
            maxProfit = Math.Max(maxProfit, prices[i] - minPrice);
            minPrice = Math.Min(minPrice, prices[i]);
        }
        
        return maxProfit;
    }
}