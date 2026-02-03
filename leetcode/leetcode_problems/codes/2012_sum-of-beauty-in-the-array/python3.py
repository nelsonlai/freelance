"""
Problem: Sum of Beauty in the Array
Difficulty: Medium
Tags: array, prefix/suffix arrays

Approach: Precompute max from left and min from right for each position
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def sumOfBeauties(self, nums: List[int]) -> int:
        n = len(nums)
        max_left = [0] * n
        min_right = [0] * n
        
        max_left[0] = nums[0]
        for i in range(1, n):
            max_left[i] = max(max_left[i - 1], nums[i])
        
        min_right[n - 1] = nums[n - 1]
        for i in range(n - 2, -1, -1):
            min_right[i] = min(min_right[i + 1], nums[i])
        
        result = 0
        for i in range(1, n - 1):
            if max_left[i - 1] < nums[i] < min_right[i + 1]:
                result += 2
            elif nums[i - 1] < nums[i] < nums[i + 1]:
                result += 1
        
        return result