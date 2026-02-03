"""
Problem: Sum of Digits in Base K
Difficulty: Easy
Tags: math

Approach: Convert to base k and sum digits
Time Complexity: O(log_k(n))
Space Complexity: O(1)
"""

class Solution:
    def sumBase(self, n: int, k: int) -> int:
        result = 0
        while n > 0:
            result += n % k
            n //= k
        return result