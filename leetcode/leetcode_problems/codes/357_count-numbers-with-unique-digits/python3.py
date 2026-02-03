"""
Problem: Count Numbers with Unique Digits
Difficulty: Medium
Tags: dp, math

Approach: Dynamic programming with memoization or tabulation
Time Complexity: O(n * m) where n and m are problem dimensions
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def countNumbersWithUniqueDigits(self, n: int) -> int:
        if n == 0:
            return 1
        
        result = 10
        available = 9
        
        for i in range(2, n + 1):
            available *= (10 - i + 1)
            result += available
        
        return result