"""
Problem: Best Time to Buy and Sell Stock with Cooldown
Difficulty: Medium
Tags: array, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        if not prices:
            return 0
        
        hold = -prices[0]
        sold = 0
        rest = 0
        
        for i in range(1, len(prices)):
            prev_hold = hold
            prev_sold = sold
            hold = max(hold, rest - prices[i])
            sold = prev_hold + prices[i]
            rest = max(rest, prev_sold)
        
        return max(sold, rest)