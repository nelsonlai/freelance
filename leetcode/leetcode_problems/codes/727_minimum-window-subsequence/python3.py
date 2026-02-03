class Solution:
    def minWindow(self, s1: str, s2: str) -> str:
        m, n = len(s1), len(s2)
        dp = [[-1] * (n + 1) for _ in range(m + 1)]
        
        for i in range(m + 1):
            dp[i][0] = i
        
        minLen = float('inf')
        start = -1
        
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if s1[i-1] == s2[j-1]:
                    dp[i][j] = dp[i-1][j-1]
                else:
                    dp[i][j] = dp[i-1][j]
            
            if dp[i][n] != -1:
                length = i - dp[i][n]
                if length < minLen:
                    minLen = length
                    start = dp[i][n]
        
        return s1[start:start+minLen] if start != -1 else ""
