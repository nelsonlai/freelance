class Solution:
    def profitableSchemes(self, n: int, minProfit: int, group: List[int], profit: List[int]) -> int:
        MOD = 10**9 + 7
        dp = [[0] * (minProfit + 1) for _ in range(n + 1)]
        dp[0][0] = 1
        
        for g, p in zip(group, profit):
            for i in range(n, -1, -1):
                for j in range(minProfit, -1, -1):
                    if i + g <= n:
                        dp[i + g][min(j + p, minProfit)] = (dp[i + g][min(j + p, minProfit)] + dp[i][j]) % MOD
        
        return sum(dp[i][minProfit] for i in range(n + 1)) % MOD
