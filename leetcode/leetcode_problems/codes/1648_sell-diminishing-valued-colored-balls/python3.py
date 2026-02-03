"""
Problem: Sell Diminishing-Valued Colored Balls
Difficulty: Medium
Tags: array, greedy, math, sort, binary search

Approach: Binary search for threshold value, calculate profit
Time Complexity: O(n log(max_inventory))
Space Complexity: O(1)
"""

MOD = 10**9 + 7

class Solution:
    def maxProfit(self, inventory: List[int], orders: int) -> int:
        def count_balls(threshold):
            count = 0
            for inv in inventory:
                if inv > threshold:
                    count += inv - threshold
            return count
        
        left, right = 0, max(inventory)
        threshold = 0
        
        while left <= right:
            mid = (left + right) // 2
            if count_balls(mid) >= orders:
                threshold = mid
                left = mid + 1
            else:
                right = mid - 1
        
        result = 0
        remaining = orders
        
        for inv in inventory:
            if inv > threshold:
                count = min(remaining, inv - threshold)
                result = (result + (inv + threshold + 1) * count // 2) % MOD
                remaining -= count
        
        if remaining > 0:
            result = (result + threshold * remaining) % MOD
        
        return result