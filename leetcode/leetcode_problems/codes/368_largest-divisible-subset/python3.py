"""
Problem: Largest Divisible Subset
Difficulty: Medium
Tags: array, dp, math, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def largestDivisibleSubset(self, nums: List[int]) -> List[int]:
        if not nums:
            return []
        
        nums.sort()
        n = len(nums)
        dp = [1] * n
        parent = [-1] * n
        max_len = 1
        max_idx = 0
        
        for i in range(1, n):
            for j in range(i):
                if nums[i] % nums[j] == 0 and dp[j] + 1 > dp[i]:
                    dp[i] = dp[j] + 1
                    parent[i] = j
                    if dp[i] > max_len:
                        max_len = dp[i]
                        max_idx = i
        
        result = []
        idx = max_idx
        while idx != -1:
            result.append(nums[idx])
            idx = parent[idx]
        
        return result[::-1]