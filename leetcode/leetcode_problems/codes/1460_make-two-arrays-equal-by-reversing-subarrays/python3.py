"""
Problem: Make Two Arrays Equal by Reversing Subarrays
Difficulty: Easy
Tags: array, hash, sort

Approach: Check if both arrays have same elements (can always rearrange)
Time Complexity: O(n) where n is length of arrays
Space Complexity: O(n) for counter
"""

from collections import Counter

class Solution:
    def canBeEqual(self, target: List[int], arr: List[int]) -> bool:
        return Counter(target) == Counter(arr)