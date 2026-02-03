"""
Problem: Sort Integers by The Number of 1 Bits
Difficulty: Easy
Tags: array, sort

Approach: Sort by bit count, then by value
Time Complexity: O(n log n) for sorting
Space Complexity: O(1) excluding result
"""

class Solution:
    def sortByBits(self, arr: List[int]) -> List[int]:
        return sorted(arr, key=lambda x: (bin(x).count('1'), x))