"""
Problem: Paint Fence
Difficulty: Medium
Tags: dp

Approach: Dynamic programming with memoization or tabulation
Time Complexity: O(n * m) where n and m are problem dimensions
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def numWays(self, n: int, k: int) -> int:
        if n == 0:
            return 0
        if n == 1:
            return k
        if n == 2:
            return k * k
        
        same = k
        diff = k * (k - 1)
        
        for i in range(3, n + 1):
            same, diff = diff, (same + diff) * (k - 1)
        
        return same + diff