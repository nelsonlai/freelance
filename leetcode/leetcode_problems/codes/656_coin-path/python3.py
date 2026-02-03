"""
Problem: Coin Path
Difficulty: Hard
Tags: array, graph, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def cheapestJump(self, coins: List[int], maxJump: int) -> List[int]:
        n = len(coins)
        if coins[-1] == -1:
            return []
        
        dp = [float('inf')] * n
        next_pos = [-1] * n
        dp[n-1] = coins[n-1]
        
        for i in range(n-2, -1, -1):
            if coins[i] == -1:
                continue
            
            for j in range(i + 1, min(i + maxJump + 1, n)):
                if dp[j] != float('inf') and dp[j] + coins[i] < dp[i]:
                    dp[i] = dp[j] + coins[i]
                    next_pos[i] = j
        
        if dp[0] == float('inf'):
            return []
        
        result = []
        i = 0
        while i != -1:
            result.append(i + 1)
            i = next_pos[i]
        
        return result