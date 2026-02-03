"""
Problem: Minimum Operations to Make Array Equal
Difficulty: Medium
Tags: array, math

Approach: Array is [1, 3, 5, ..., 2n-1]. Target is n. Calculate sum of differences
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def minOperations(self, n: int) -> int:
        # Target value is n
        # For odd n: operations = 1 + 3 + 5 + ... + (n-1) = (n//2) * (n//2)
        # For even n: operations = 2 + 4 + 6 + ... + (n-1) = (n//2) * (n//2 + 1)
        if n % 2 == 1:
            return (n // 2) * (n // 2 + 1)
        else:
            return (n // 2) * (n // 2)