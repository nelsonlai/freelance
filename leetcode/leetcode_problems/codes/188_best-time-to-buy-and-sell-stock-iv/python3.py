"""
Problem: Best Time to Buy and Sell Stock IV
Difficulty: Hard
Tags: array, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def maxProfit(self, k: int, prices: List[int]) -> int:
        if not prices or k == 0:
            return 0
        
        n = len(prices)
        if k >= n // 2:
            profit = 0
            for i in range(1, n):
                if prices[i] > prices[i-1]:
                    profit += prices[i] - prices[i-1]
            return profit
        
        buy = [-float('inf')] * (k + 1)
        sell = [0] * (k + 1)
        
        for price in prices:
            for i in range(1, k + 1):
                buy[i] = max(buy[i], sell[i-1] - price)
                sell[i] = max(sell[i], buy[i] + price)
        
        return sell[k]