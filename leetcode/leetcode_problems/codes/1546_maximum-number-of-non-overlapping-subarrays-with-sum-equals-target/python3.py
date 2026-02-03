"""
Problem: Maximum Number of Non-Overlapping Subarrays With Sum Equals Target
Difficulty: Medium
Tags: array, greedy, hash

Approach: Greedy - use prefix sum, track last end position, take earliest valid subarray
Time Complexity: O(n) where n is length of nums
Space Complexity: O(n) for prefix map
"""

class Solution:
    def maxNonOverlapping(self, nums: List[int], target: int) -> int:
        prefix_sum = {0: -1}
        current_sum = 0
        count = 0
        last_end = -1
        
        for i, num in enumerate(nums):
            current_sum += num
            if current_sum - target in prefix_sum:
                prev_idx = prefix_sum[current_sum - target]
                if prev_idx >= last_end:
                    count += 1
                    last_end = i
            prefix_sum[current_sum] = i
        
        return count