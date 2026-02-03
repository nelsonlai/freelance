"""
Problem: Stone Game VIII
Difficulty: Hard
Tags: array, dp, math, prefix sum

Approach: DP - dp[i] = max score difference starting from position i
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def stoneGameVIII(self, stones: List[int]) -> int:
        n = len(stones)
        prefix = [0]
        for stone in stones:
            prefix.append(prefix[-1] + stone)
        
        # dp[i] = max score difference when starting from position i
        dp = [0] * n
        dp[n - 1] = prefix[n]  # Take all remaining stones
        
        # Backward DP
        for i in range(n - 2, 0, -1):
            # Option 1: Take from position i, opponent gets dp[i+1]
            # Option 2: Don't take, get dp[i+1]
            dp[i] = max(prefix[i + 1] - dp[i + 1], dp[i + 1])
        
        return dp[1]