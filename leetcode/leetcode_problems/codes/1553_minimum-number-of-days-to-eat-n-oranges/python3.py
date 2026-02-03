"""
Problem: Minimum Number of Days to Eat N Oranges
Difficulty: Hard
Tags: dp

Approach: Memoized DFS - try eating 1, or n/2 if divisible by 2, or n/3 if divisible by 3
Time Complexity: O(log^2 n) with memoization
Space Complexity: O(log^2 n) for memoization
"""

from functools import lru_cache

class Solution:
    @lru_cache(None)
    def minDays(self, n: int) -> int:
        if n <= 1:
            return n
        
        result = n
        # Try eating 1 orange
        result = min(result, 1 + self.minDays(n - 1))
        
        # Try eating n/2 if divisible by 2
        if n % 2 == 0:
            result = min(result, 1 + self.minDays(n // 2))
        
        # Try eating 2n/3 if divisible by 3
        if n % 3 == 0:
            result = min(result, 1 + self.minDays(n // 3))
        
        return result