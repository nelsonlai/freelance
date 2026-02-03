"""
Problem: Arithmetic Slices II - Subsequence
Difficulty: Hard
Tags: array, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

from collections import defaultdict

class Solution:
    def numberOfArithmeticSlices(self, nums: List[int]) -> int:
        n = len(nums)
        dp = [defaultdict(int) for _ in range(n)]
        total = 0
        
        for i in range(n):
            for j in range(i):
                diff = nums[i] - nums[j]
                count = dp[j].get(diff, 0)
                dp[i][diff] += count + 1
                total += count
        
        return total