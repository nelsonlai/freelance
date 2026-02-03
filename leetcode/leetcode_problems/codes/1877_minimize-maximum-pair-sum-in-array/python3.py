"""
Problem: Minimize Maximum Pair Sum in Array
Difficulty: Medium
Tags: array, greedy, sort

Approach: Sort, pair smallest with largest
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def minPairSum(self, nums: List[int]) -> int:
        nums.sort()
        result = 0
        n = len(nums)
        for i in range(n // 2):
            result = max(result, nums[i] + nums[n - 1 - i])
        return result