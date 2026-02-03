"""
Problem: Number of Ways to Separate Numbers
Difficulty: Hard
Tags: array, string, dp

Approach: DP - dp[i][j] = ways to form valid sequence ending at position i with last number of length j
Time Complexity: O(n^2) where n is length
Space Complexity: O(n^2)
"""

class Solution:
    def numberOfCombinations(self, num: str) -> int:
        MOD = 10**9 + 7
        n = len(num)
        
        if num[0] == '0':
            return 0
        
        # dp[i][j] = number of ways to form sequence ending at i with last number of length j
        dp = [[0] * (n + 1) for _ in range(n + 1)]
        dp[0][0] = 1
        
        # Precompute LCP (longest common prefix) for string comparison
        lcp = [[0] * (n + 1) for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if num[i] == num[j]:
                    lcp[i][j] = 1 + lcp[i + 1][j + 1]
                else:
                    lcp[i][j] = 0
        
        def compare(i, j, len_val):
            # Compare num[i-len:i] and num[j-len:j]
            if i < len_val or j < len_val:
                return False
            common = lcp[i - len_val][j - len_val]
            if common >= len_val:
                return True
            return num[i - len_val + common] >= num[j - len_val + common]
        
        for i in range(1, n + 1):
            for j in range(1, i + 1):
                if num[i - j] == '0':
                    continue
                
                if i - j == 0:
                    dp[i][j] = 1
                else:
                    # Try all possible previous lengths
                    for k in range(1, min(j, i - j) + 1):
                        if compare(i - j, i, k):
                            dp[i][j] = (dp[i][j] + dp[i - j][k]) % MOD
                    # Also try shorter previous number
                    if i - j >= j:
                        for k in range(1, j):
                            dp[i][j] = (dp[i][j] + dp[i - j][k]) % MOD
        
        return sum(dp[n]) % MOD