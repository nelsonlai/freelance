"""
Problem: Number of Ways of Cutting a Pizza
Difficulty: Hard
Tags: array, dp

Approach: DP with memoization - dp[r][c][cuts] = ways to cut from (r,c) with cuts remaining
Time Complexity: O(rows * cols * k * (rows + cols))
Space Complexity: O(rows * cols * k)
"""

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        MOD = 10**9 + 7
        rows, cols = len(pizza), len(pizza[0])
        
        # Prefix sum for apples
        prefix = [[0] * (cols + 1) for _ in range(rows + 1)]
        for i in range(rows - 1, -1, -1):
            for j in range(cols - 1, -1, -1):
                prefix[i][j] = (prefix[i+1][j] + prefix[i][j+1] - 
                               prefix[i+1][j+1] + (1 if pizza[i][j] == 'A' else 0))
        
        memo = {}
        
        def has_apple(r1, c1, r2, c2):
            return prefix[r1][c1] - prefix[r2][c1] - prefix[r1][c2] + prefix[r2][c2] > 0
        
        def dp(r, c, cuts):
            if (r, c, cuts) in memo:
                return memo[(r, c, cuts)]
            
            if cuts == 0:
                return 1 if has_apple(r, c, rows, cols) else 0
            
            result = 0
            
            # Cut horizontally
            for i in range(r + 1, rows):
                if has_apple(r, c, i, cols):
                    result = (result + dp(i, c, cuts - 1)) % MOD
            
            # Cut vertically
            for j in range(c + 1, cols):
                if has_apple(r, c, rows, j):
                    result = (result + dp(r, j, cuts - 1)) % MOD
            
            memo[(r, c, cuts)] = result
            return result
        
        return dp(0, 0, k - 1)