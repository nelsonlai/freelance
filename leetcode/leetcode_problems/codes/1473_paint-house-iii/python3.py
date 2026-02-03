"""
Problem: Paint House III
Difficulty: Hard
Tags: array, dp

Approach: DP - dp[i][j][k] = min cost painting first i houses, last color j, k neighborhoods
Time Complexity: O(m * n^2 * target)
Space Complexity: O(m * n * target)
"""

class Solution:
    def minCost(self, houses: List[int], cost: List[List[int]], m: int, n: int, target: int) -> int:
        dp = [[[float('inf')] * (target + 1) for _ in range(n + 1)] for _ in range(m + 1)]
        dp[0][0][0] = 0
        
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if houses[i-1] != 0 and houses[i-1] != j:
                    continue
                
                paint_cost = 0 if houses[i-1] == j else cost[i-1][j-1]
                
                for k in range(1, target + 1):
                    for prev_color in range(n + 1):
                        if prev_color == j:
                            dp[i][j][k] = min(dp[i][j][k], dp[i-1][j][k] + paint_cost)
                        else:
                            dp[i][j][k] = min(dp[i][j][k], dp[i-1][prev_color][k-1] + paint_cost)
        
        result = min(dp[m][j][target] for j in range(1, n + 1))
        return result if result != float('inf') else -1