"""
Problem: Largest Unique Number
Difficulty: Easy
Tags: array, hash, sort

Approach: Count frequency, find largest number that appears exactly once
Time Complexity: O(n) where n is the length of nums
Space Complexity: O(n) for frequency map
"""

class Solution:
    def largestUniqueNumber(self, nums: List[int]) -> int:
        from collections import Counter
        freq = Counter(nums)
        unique = [num for num, count in freq.items() if count == 1]
        return max(unique) if unique else -1