"""
Problem: Contiguous Array
Difficulty: Medium
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def findMaxLength(self, nums: List[int]) -> int:
        count = 0
        max_length = 0
        count_map = defaultdict(int)
        count_map[0] = -1
        
        for i, num in enumerate(nums):
            count += 1 if num == 1 else -1
            if count in count_map:
                max_length = max(max_length, i - count_map[count])
            else:
                count_map[count] = i
        
        return max_length