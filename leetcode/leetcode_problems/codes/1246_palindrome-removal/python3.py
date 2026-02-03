"""
Problem: Palindrome Removal
Difficulty: Hard
Tags: array, dp

Approach: DP - dp[i][j] = minimum moves to remove arr[i:j+1]
Time Complexity: O(n^3) where n is length of arr
Space Complexity: O(n^2) for DP table
"""

class Solution:
    def minimumMoves(self, arr: List[int]) -> int:
        n = len(arr)
        dp = [[0] * n for _ in range(n)]
        
        for i in range(n):
            dp[i][i] = 1
        
        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                dp[i][j] = float('inf')
                
                if arr[i] == arr[j]:
                    if length == 2:
                        dp[i][j] = 1
                    else:
                        dp[i][j] = dp[i+1][j-1]
                
                for k in range(i, j):
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j])
        
        return dp[0][n-1]