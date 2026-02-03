"""
Problem: Longest Harmonious Subsequence
Difficulty: Easy
Tags: array, hash, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def findLHS(self, nums: List[int]) -> int:
        count = Counter(nums)
        max_length = 0
        
        for num in count:
            if num + 1 in count:
                max_length = max(max_length, count[num] + count[num + 1])
        
        return max_length