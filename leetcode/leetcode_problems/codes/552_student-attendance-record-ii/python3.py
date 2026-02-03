"""
Problem: Student Attendance Record II
Difficulty: Hard
Tags: string, dp

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def checkRecord(self, n: int) -> int:
        MOD = 10**9 + 7
        
        if n == 0:
            return 0
        if n == 1:
            return 3
        
        dp = [[[0] * 3 for _ in range(2)] for _ in range(n + 1)]
        dp[0][0][0] = 1
        
        for i in range(1, n + 1):
            for a in range(2):
                for l in range(3):
                    dp[i][a][0] = (dp[i][a][0] + dp[i-1][a][l]) % MOD
                    if a < 1:
                        dp[i][a+1][0] = (dp[i][a+1][0] + dp[i-1][a][l]) % MOD
                    if l < 2:
                        dp[i][a][l+1] = (dp[i][a][l+1] + dp[i-1][a][l]) % MOD
        
        result = 0
        for a in range(2):
            for l in range(3):
                result = (result + dp[n][a][l]) % MOD
        
        return result