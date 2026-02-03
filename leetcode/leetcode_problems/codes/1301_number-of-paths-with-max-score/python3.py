"""
Problem: Number of Paths with Max Score
Difficulty: Hard
Tags: array, tree, dp

Approach: DP - track max score and number of paths for each cell
Time Complexity: O(n^2) where n is board size
Space Complexity: O(n^2) for DP table
"""

class Solution:
    def pathsWithMaxScore(self, board: List[str]) -> List[int]:
        n = len(board)
        MOD = 10**9 + 7
        directions = [(-1, -1), (-1, 0), (0, -1)]
        
        # dp[i][j] = [max_score, num_paths]
        dp = [[[0, 0] for _ in range(n + 1)] for _ in range(n + 1)]
        dp[n-1][n-1] = [0, 1]
        
        for i in range(n - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if board[i][j] == 'X' or board[i][j] == 'S':
                    continue
                
                max_score = 0
                num_paths = 0
                
                for di, dj in directions:
                    ni, nj = i + di, j + dj
                    if dp[ni][nj][1] > 0:
                        score = dp[ni][nj][0]
                        if score > max_score:
                            max_score = score
                            num_paths = dp[ni][nj][1]
                        elif score == max_score:
                            num_paths = (num_paths + dp[ni][nj][1]) % MOD
                
                if num_paths > 0:
                    value = int(board[i][j]) if board[i][j].isdigit() else 0
                    dp[i][j] = [max_score + value, num_paths]
        
        return dp[0][0]