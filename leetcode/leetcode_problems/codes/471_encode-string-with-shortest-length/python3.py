"""
Problem: Encode String with Shortest Length
Difficulty: Hard
Tags: string, dp

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def encode(self, s: str) -> str:
        n = len(s)
        dp = [[''] * n for _ in range(n)]
        
        for length in range(1, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                substr = s[i:j+1]
                dp[i][j] = substr
                
                if length > 4:
                    for k in range(i, j):
                        if len(dp[i][k]) + len(dp[k+1][j]) < len(dp[i][j]):
                            dp[i][j] = dp[i][k] + dp[k+1][j]
                    
                    for k in range(1, length // 2 + 1):
                        if length % k == 0:
                            pattern = s[i:i+k]
                            if substr == pattern * (length // k):
                                encoded = str(length // k) + '[' + dp[i][i+k-1] + ']'
                                if len(encoded) < len(dp[i][j]):
                                    dp[i][j] = encoded
        
        return dp[0][n-1]