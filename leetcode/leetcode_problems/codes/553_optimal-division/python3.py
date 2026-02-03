"""
Problem: Optimal Division
Difficulty: Medium
Tags: array, string, dp, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def optimalDivision(self, nums: List[int]) -> str:
        if len(nums) == 1:
            return str(nums[0])
        if len(nums) == 2:
            return str(nums[0]) + "/" + str(nums[1])
        
        result = str(nums[0]) + "/(" + str(nums[1])
        for i in range(2, len(nums)):
            result += "/" + str(nums[i])
        result += ")"
        
        return result