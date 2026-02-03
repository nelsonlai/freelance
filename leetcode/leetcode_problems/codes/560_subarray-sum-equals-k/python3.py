"""
Problem: Subarray Sum Equals K
Difficulty: Medium
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        count = defaultdict(int)
        count[0] = 1
        prefix_sum = 0
        result = 0
        
        for num in nums:
            prefix_sum += num
            result += count[prefix_sum - k]
            count[prefix_sum] += 1
        
        return result