"""
Problem: Maximum Number of Consecutive Values You Can Make
Difficulty: Medium
Tags: array, greedy, sort

Approach: Sort coins, build consecutive values from smallest
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def getMaximumConsecutive(self, coins: List[int]) -> int:
        coins.sort()
        current_max = 0
        
        for coin in coins:
            if coin > current_max + 1:
                break
            current_max += coin
        
        return current_max + 1