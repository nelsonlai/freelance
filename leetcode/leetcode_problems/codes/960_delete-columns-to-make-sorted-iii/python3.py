"""
Problem: Delete Columns to Make Sorted III
Difficulty: Hard
Tags: array, string, graph, dp, sort

Approach: DP - find longest increasing subsequence of columns, answer is m - LIS
Time Complexity: O(m^2 * n) where m is string length, n is number of strings
Space Complexity: O(m) for DP
"""

class Solution:
    def minDeletionSize(self, strs: List[str]) -> int:
        n = len(strs)
        m = len(strs[0])
        
        # dp[i] = length of longest increasing subsequence ending at column i
        dp = [1] * m
        
        for i in range(1, m):
            for j in range(i):
                # Check if column j can come before column i
                if all(strs[k][j] <= strs[k][i] for k in range(n)):
                    dp[i] = max(dp[i], dp[j] + 1)
        
        return m - max(dp)