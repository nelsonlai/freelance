"""
Problem: Count Odd Numbers in an Interval Range
Difficulty: Easy
Tags: math

Approach: Count odds using formula: (high - low + 1 + (low % 2)) // 2
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def countOdds(self, low: int, high: int) -> int:
        return (high - low + 1 + (low % 2)) // 2