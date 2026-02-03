"""
Problem: Sort Array by Increasing Frequency
Difficulty: Easy
Tags: array, hash, sort

Approach: Count frequency, sort by frequency then by value (descending for same frequency)
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for frequency map
"""

from collections import Counter

class Solution:
    def frequencySort(self, nums: List[int]) -> List[int]:
        freq = Counter(nums)
        return sorted(nums, key=lambda x: (freq[x], -x))