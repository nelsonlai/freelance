"""
Problem: Maximum Gap
Difficulty: Medium
Tags: array, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def maximumGap(self, nums: List[int]) -> int:
        if len(nums) < 2:
            return 0
        
        nums.sort()
        max_gap = 0
        
        for i in range(1, len(nums)):
            max_gap = max(max_gap, nums[i] - nums[i - 1])
        
        return max_gap