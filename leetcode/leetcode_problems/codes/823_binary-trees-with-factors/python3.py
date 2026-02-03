class Solution:
    def numFactoredBinaryTrees(self, arr: List[int]) -> int:
        MOD = 10**9 + 7
        arr.sort()
        dp = {num: 1 for num in arr}
        
        for i, num in enumerate(arr):
            for j in range(i):
                if num % arr[j] == 0:
                    factor = num // arr[j]
                    if factor in dp:
                        dp[num] = (dp[num] + dp[arr[j]] * dp[factor]) % MOD
        
        return sum(dp.values()) % MOD
