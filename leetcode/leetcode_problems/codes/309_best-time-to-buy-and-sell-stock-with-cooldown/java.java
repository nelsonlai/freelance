/**
 * Problem: Best Time to Buy and Sell Stock with Cooldown
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int maxProfit(int[] prices) {
        if (prices == null || prices.length == 0) {
            return 0;
        }
        
        int hold = -prices[0];
        int sold = 0;
        int rest = 0;
        
        for (int i = 1; i < prices.length; i++) {
            int prevHold = hold;
            int prevSold = sold;
            hold = Math.max(hold, rest - prices[i]);
            sold = prevHold + prices[i];
            rest = Math.max(rest, prevSold);
        }
        
        return Math.max(sold, rest);
    }
}