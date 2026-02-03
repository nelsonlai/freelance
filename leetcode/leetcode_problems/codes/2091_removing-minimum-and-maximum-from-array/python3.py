"""
Problem: Removing Minimum and Maximum From Array
Difficulty: Medium
Tags: array, greedy

Approach: Find min/max indices, calculate minimum deletions from left, right, or both
Time Complexity: O(n) where n is array length
Space Complexity: O(1)
"""

class Solution:
    def minimumDeletions(self, nums: List[int]) -> int:
        n = len(nums)
        min_idx = nums.index(min(nums))
        max_idx = nums.index(max(nums))
        
        # Ensure min_idx < max_idx
        if min_idx > max_idx:
            min_idx, max_idx = max_idx, min_idx
        
        # Three options:
        # 1. Remove both from left: max_idx + 1
        # 2. Remove both from right: n - min_idx
        # 3. Remove one from left, one from right: (min_idx + 1) + (n - max_idx)
        
        option1 = max_idx + 1
        option2 = n - min_idx
        option3 = (min_idx + 1) + (n - max_idx)
        
        return min(option1, option2, option3)