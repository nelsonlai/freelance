from collections import Counter

class Solution:
    def deleteAndEarn(self, nums: List[int]) -> int:
        count = Counter(nums)
        maxNum = max(nums)
        
        dp = [0] * (maxNum + 1)
        dp[1] = count.get(1, 0)
        
        for i in range(2, maxNum + 1):
            dp[i] = max(dp[i - 1], dp[i - 2] + i * count.get(i, 0))
        
        return dp[maxNum]
