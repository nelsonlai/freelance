"""
Problem: House Robber II
Difficulty: Medium
Tags: array, tree, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def rob(self, nums: List[int]) -> int:
        if len(nums) == 1:
            return nums[0]
        
        def rob_linear(houses):
            prev2 = 0
            prev1 = 0
            for house in houses:
                current = max(prev1, prev2 + house)
                prev2 = prev1
                prev1 = current
            return prev1
        
        return max(rob_linear(nums[:-1]), rob_linear(nums[1:]))