"""
Problem: Degree of an Array
Difficulty: Easy
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def findShortestSubArray(self, nums: List[int]) -> int:
        first = {}
        count = defaultdict(int)
        max_count = 0
        result = len(nums)
        
        for i, num in enumerate(nums):
            if num not in first:
                first[num] = i
            count[num] += 1
            if count[num] > max_count:
                max_count = count[num]
                result = i - first[num] + 1
            elif count[num] == max_count:
                result = min(result, i - first[num] + 1)
        
        return result