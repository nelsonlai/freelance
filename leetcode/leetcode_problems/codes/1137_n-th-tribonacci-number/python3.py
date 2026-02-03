"""
Problem: N-th Tribonacci Number
Difficulty: Easy
Tags: dp, math

Approach: Dynamic programming - T(n) = T(n-1) + T(n-2) + T(n-3)
Time Complexity: O(n)
Space Complexity: O(1) using iterative approach
"""

class Solution:
    def tribonacci(self, n: int) -> int:
        if n == 0:
            return 0
        if n <= 2:
            return 1
        
        a, b, c = 0, 1, 1
        for i in range(3, n + 1):
            a, b, c = b, c, a + b + c
        
        return c