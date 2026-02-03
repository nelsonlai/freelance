"""
Problem: Sum of Absolute Differences in a Sorted Array
Difficulty: Medium
Tags: array, math, sort, prefix sum

Approach: Use prefix sum - for each index, calculate sum from left and right
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def getSumAbsoluteDifferences(self, nums: List[int]) -> List[int]:
        n = len(nums)
        total_sum = sum(nums)
        left_sum = 0
        result = []
        
        for i in range(n):
            right_sum = total_sum - left_sum - nums[i]
            left_count = i
            right_count = n - i - 1
            
            diff = (nums[i] * left_count - left_sum) + (right_sum - nums[i] * right_count)
            result.append(diff)
            left_sum += nums[i]
        
        return result