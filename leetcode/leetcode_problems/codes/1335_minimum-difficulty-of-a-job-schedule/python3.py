"""
Problem: Minimum Difficulty of a Job Schedule
Difficulty: Hard
Tags: array, dp

Approach: DP - dp[i][j] = min difficulty to schedule first i jobs in j days
Time Complexity: O(n^2 * d) where n is jobs, d is days
Space Complexity: O(n * d) for DP table
"""

class Solution:
    def minDifficulty(self, jobDifficulty: List[int], d: int) -> int:
        n = len(jobDifficulty)
        if n < d:
            return -1
        
        dp = [[float('inf')] * (d + 1) for _ in range(n + 1)]
        dp[0][0] = 0
        
        for i in range(1, n + 1):
            for j in range(1, min(i, d) + 1):
                max_difficulty = 0
                for k in range(i, j - 1, -1):
                    max_difficulty = max(max_difficulty, jobDifficulty[k - 1])
                    dp[i][j] = min(dp[i][j], dp[k - 1][j - 1] + max_difficulty)
        
        return dp[n][d]