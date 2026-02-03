"""
Problem: Number of Good Pairs
Difficulty: Easy
Tags: array, math, hash

Approach: Count frequency of each number, for n occurrences, there are n*(n-1)/2 pairs
Time Complexity: O(n) where n is length of nums
Space Complexity: O(n) for frequency map
"""

from collections import Counter

class Solution:
    def numIdenticalPairs(self, nums: List[int]) -> int:
        freq = Counter(nums)
        return sum(count * (count - 1) // 2 for count in freq.values())