"""
Problem: Number of Ways to Form a Target String Given a Dictionary
Difficulty: Hard
Tags: array, string, dp

Approach: DP - dp[i][j] = ways to form target[0:i] using first j columns
Time Complexity: O(m * n * k) where m is target length, n is word length, k is dictionary size
Space Complexity: O(m * n)
"""

MOD = 10**9 + 7

class Solution:
    def numWays(self, words: List[str], target: str) -> int:
        m, n = len(target), len(words[0])
        
        # Count frequency of each character at each column
        freq = [[0] * 26 for _ in range(n)]
        for word in words:
            for j in range(n):
                freq[j][ord(word[j]) - ord('a')] += 1
        
        # DP: dp[i][j] = ways to form target[0:i] using columns 0:j
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        dp[0][0] = 1
        
        for i in range(m + 1):
            for j in range(n):
                if i < m:
                    char_idx = ord(target[i]) - ord('a')
                    dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j] * freq[j][char_idx]) % MOD
                dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % MOD
        
        return dp[m][n]