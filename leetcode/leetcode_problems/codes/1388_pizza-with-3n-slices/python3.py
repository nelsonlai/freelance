"""
Problem: Pizza With 3n Slices
Difficulty: Hard
Tags: array, dp, greedy, queue, heap

Approach: DP - similar to house robber II, can't take adjacent slices
Time Complexity: O(n^2) where n is number of slices
Space Complexity: O(n) for DP table
"""

class Solution:
    def maxSizeSlices(self, slices: List[int]) -> int:
        n = len(slices)
        k = n // 3
        
        def solve(arr):
            m = len(arr)
            dp = [[0] * (k + 1) for _ in range(m + 1)]
            
            for i in range(1, m + 1):
                for j in range(1, k + 1):
                    if i == 1:
                        dp[i][j] = arr[0]
                    else:
                        dp[i][j] = max(dp[i-1][j], dp[i-2][j-1] + arr[i-1])
            
            return dp[m][k]
        
        return max(solve(slices[:-1]), solve(slices[1:]))