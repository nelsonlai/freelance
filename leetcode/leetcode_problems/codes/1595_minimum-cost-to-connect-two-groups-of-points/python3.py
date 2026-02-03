"""
Problem: Minimum Cost to Connect Two Groups of Points
Difficulty: Hard
Tags: array, dp

Approach: DP with bitmask - dp[i][mask] = min cost connecting first i points from group1 with mask points from group2
Time Complexity: O(m * n * 2^n) where m, n are group sizes
Space Complexity: O(m * 2^n) for DP table
"""

class Solution:
    def connectTwoGroups(self, cost: List[List[int]]) -> int:
        m, n = len(cost), len(cost[0])
        
        min_cost_group2 = [min(cost[i][j] for i in range(m)) for j in range(n)]
        
        @lru_cache(None)
        def dp(i, mask):
            if i == m:
                result = 0
                for j in range(n):
                    if not (mask & (1 << j)):
                        result += min_cost_group2[j]
                return result
            
            result = float('inf')
            for j in range(n):
                result = min(result, cost[i][j] + dp(i + 1, mask | (1 << j)))
            
            return result
        
        return dp(0, 0)