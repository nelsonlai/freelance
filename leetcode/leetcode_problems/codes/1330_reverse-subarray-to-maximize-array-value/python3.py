"""
Problem: Reverse Subarray To Maximize Array Value
Difficulty: Hard
Tags: array, greedy, math

Approach: Calculate base value, try reversing at boundaries to maximize gain
Time Complexity: O(n) where n is length of nums
Space Complexity: O(1)
"""

class Solution:
    def maxValueAfterReverse(self, nums: List[int]) -> int:
        n = len(nums)
        base = sum(abs(nums[i] - nums[i+1]) for i in range(n-1))
        
        # Try reversing at start
        gain1 = max(abs(nums[0] - nums[j+1]) - abs(nums[j] - nums[j+1]) 
                   for j in range(n-1))
        
        # Try reversing at end
        gain2 = max(abs(nums[i-1] - nums[-1]) - abs(nums[i-1] - nums[i]) 
                   for i in range(1, n))
        
        # Try reversing in middle
        gain3 = 0
        for i in range(n-1):
            for j in range(i+1, n-1):
                gain3 = max(gain3, 
                           abs(nums[i] - nums[j+1]) + abs(nums[j] - nums[i+1]) -
                           abs(nums[i] - nums[i+1]) - abs(nums[j] - nums[j+1]))
        
        return base + max(gain1, gain2, gain3)