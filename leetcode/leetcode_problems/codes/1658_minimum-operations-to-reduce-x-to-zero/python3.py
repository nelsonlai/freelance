"""
Problem: Minimum Operations to Reduce X to Zero
Difficulty: Medium
Tags: array, hash, search, sliding window

Approach: Find longest subarray with sum = total - x, answer = n - length
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def minOperations(self, nums: List[int], x: int) -> int:
        target = sum(nums) - x
        if target < 0:
            return -1
        if target == 0:
            return len(nums)
        
        left = 0
        current_sum = 0
        max_len = -1
        
        for right in range(len(nums)):
            current_sum += nums[right]
            
            while current_sum > target:
                current_sum -= nums[left]
                left += 1
            
            if current_sum == target:
                max_len = max(max_len, right - left + 1)
        
        return len(nums) - max_len if max_len != -1 else -1