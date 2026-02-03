"""
Problem: Sum of Unique Elements
Difficulty: Easy
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def sumOfUnique(self, nums: List[int]) -> int:
        count = Counter(nums)
        return sum(num for num, freq in count.items() if freq == 1)