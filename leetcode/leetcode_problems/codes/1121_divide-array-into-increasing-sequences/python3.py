"""
Problem: Divide Array Into Increasing Sequences
Difficulty: Hard
Tags: array, sort

Approach: Count frequency of each number, check if max frequency * k <= n
Time Complexity: O(n) where n is the length of nums
Space Complexity: O(n) for frequency map
"""

class Solution:
    def canDivideIntoSubsequences(self, nums: List[int], k: int) -> bool:
        from collections import Counter
        freq = Counter(nums)
        max_freq = max(freq.values())
        return max_freq * k <= len(nums)