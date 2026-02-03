"""
Problem: Longest Arithmetic Subsequence of Given Difference
Difficulty: Medium
Tags: array, dp, hash

Approach: DP with hash map - dp[num] = length ending at num
Time Complexity: O(n) where n is length of arr
Space Complexity: O(n) for hash map
"""

class Solution:
    def longestSubsequence(self, arr: List[int], difference: int) -> int:
        dp = {}
        max_len = 1
        
        for num in arr:
            prev = num - difference
            if prev in dp:
                dp[num] = dp[prev] + 1
            else:
                dp[num] = 1
            max_len = max(max_len, dp[num])
        
        return max_len