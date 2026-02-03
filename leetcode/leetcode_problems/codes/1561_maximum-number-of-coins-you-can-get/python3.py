"""
Problem: Maximum Number of Coins You Can Get
Difficulty: Medium
Tags: array, greedy, math, sort

Approach: Sort, take second largest from each triple starting from end
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def maxCoins(self, piles: List[int]) -> int:
        piles.sort()
        n = len(piles)
        result = 0
        
        # Take second largest from each triple
        for i in range(n // 3, n, 2):
            result += piles[i]
        
        return result