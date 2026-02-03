"""
Problem: Maximum Size Subarray Sum Equals k
Difficulty: Medium
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def maxSubArrayLen(self, nums: List[int], k: int) -> int:
        prefix_sum = 0
        sum_map = {0: -1}
        max_length = 0
        
        for i, num in enumerate(nums):
            prefix_sum += num
            if prefix_sum - k in sum_map:
                max_length = max(max_length, i - sum_map[prefix_sum - k])
            if prefix_sum not in sum_map:
                sum_map[prefix_sum] = i
        
        return max_length