"""
Problem: Minimum Cost to Cut a Stick
Difficulty: Hard
Tags: array, dp, sort

Approach: DP - dp[i][j] = min cost to cut stick from cuts[i] to cuts[j]
Time Complexity: O(m^3) where m is number of cuts
Space Complexity: O(m^2) for DP table
"""

class Solution:
    def minCost(self, n: int, cuts: List[int]) -> int:
        cuts = sorted([0] + cuts + [n])
        m = len(cuts)
        dp = [[0] * m for _ in range(m)]
        
        for length in range(2, m):
            for i in range(m - length):
                j = i + length
                dp[i][j] = float('inf')
                for k in range(i + 1, j):
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + cuts[j] - cuts[i])
        
        return dp[0][m-1]