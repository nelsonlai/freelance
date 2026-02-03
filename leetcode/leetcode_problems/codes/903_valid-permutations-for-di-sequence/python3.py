class Solution:
    def numPermsDISequence(self, s: str) -> int:
        n = len(s)
        MOD = 10**9 + 7
        dp = [1] * (n + 1)
        
        for i in range(n):
            new_dp = [0] * (n + 1)
            if s[i] == 'I':
                for j in range(n - i):
                    new_dp[j] = sum(dp[:j+1]) % MOD
            else:
                for j in range(n - i):
                    new_dp[j] = sum(dp[j+1:]) % MOD
            dp = new_dp
        
        return dp[0]
