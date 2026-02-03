class Solution:
    def atMostNGivenDigitSet(self, digits: List[str], n: int) -> int:
        s = str(n)
        k = len(s)
        dp = [0] * k + [1]
        
        for i in range(k - 1, -1, -1):
            for d in digits:
                if d < s[i]:
                    dp[i] += len(digits) ** (k - i - 1)
                elif d == s[i]:
                    dp[i] += dp[i + 1]
        
        return dp[0] + sum(len(digits) ** i for i in range(1, k))
