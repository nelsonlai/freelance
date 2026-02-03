"""
Problem: Rotate Function
Difficulty: Medium
Tags: array, dp, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def maxRotateFunction(self, nums: List[int]) -> int:
        n = len(nums)
        total_sum = sum(nums)
        f0 = sum(i * nums[i] for i in range(n))
        max_val = f0
        
        for i in range(1, n):
            f0 = f0 + total_sum - n * nums[n - i]
            max_val = max(max_val, f0)
        
        return max_val