"""
Problem: Longest Arithmetic Subsequence
Difficulty: Medium
Tags: array, dp, hash, search

Approach: DP - for each position and difference, track longest sequence
Time Complexity: O(n^2)
Space Complexity: O(n^2) for DP dictionary
"""

class Solution:
    def longestArithSeqLength(self, nums: List[int]) -> int:
        dp = {}
        n = len(nums)
        
        for i in range(n):
            for j in range(i):
                diff = nums[i] - nums[j]
                dp[(i, diff)] = dp.get((j, diff), 1) + 1
        
        return max(dp.values()) if dp else 1