"""
Problem: 2 Keys Keyboard
Difficulty: Medium
Tags: dp, math

Approach: Dynamic programming with memoization or tabulation
Time Complexity: O(n * m) where n and m are problem dimensions
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def minSteps(self, n: int) -> int:
        if n == 1:
            return 0
        
        result = 0
        d = 2
        
        while d * d <= n:
            while n % d == 0:
                result += d
                n //= d
            d += 1
        
        if n > 1:
            result += n
        
        return result