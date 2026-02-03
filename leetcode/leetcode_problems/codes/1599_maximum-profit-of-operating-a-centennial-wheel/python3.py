"""
Problem: Maximum Profit of Operating a Centennial Wheel
Difficulty: Medium
Tags: array

Approach: Simulate wheel operations, track profit at each rotation
Time Complexity: O(n + total_customers) where n is length of customers
Space Complexity: O(1)
"""

class Solution:
    def minOperationsMaxProfit(self, customers: List[int], boardingCost: int, runningCost: int) -> int:
        waiting = 0
        profit = 0
        max_profit = 0
        result = -1
        i = 0
        
        while waiting > 0 or i < len(customers):
            if i < len(customers):
                waiting += customers[i]
            
            board = min(4, waiting)
            waiting -= board
            profit += board * boardingCost - runningCost
            
            if profit > max_profit:
                max_profit = profit
                result = i + 1
            
            i += 1
        
        return result