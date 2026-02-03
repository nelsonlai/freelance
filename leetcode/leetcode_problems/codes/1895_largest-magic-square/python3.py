"""
Problem: Largest Magic Square
Difficulty: Medium
Tags: array, prefix sum

Approach: Try all sizes, use prefix sum to check if magic square
Time Complexity: O(m * n * min(m,n)^2) where m, n are dimensions
Space Complexity: O(m * n)
"""

class Solution:
    def largestMagicSquare(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        
        # Prefix sums
        row_sum = [[0] * (n + 1) for _ in range(m)]
        col_sum = [[0] * (m + 1) for _ in range(n)]
        
        for i in range(m):
            for j in range(n):
                row_sum[i][j+1] = row_sum[i][j] + grid[i][j]
                col_sum[j][i+1] = col_sum[j][i] + grid[i][j]
        
        result = 1
        
        for size in range(2, min(m, n) + 1):
            for i in range(m - size + 1):
                for j in range(n - size + 1):
                    # Check row sums
                    target = row_sum[i][j+size] - row_sum[i][j]
                    valid = True
                    
                    for r in range(i, i + size):
                        if row_sum[r][j+size] - row_sum[r][j] != target:
                            valid = False
                            break
                    
                    if not valid:
                        continue
                    
                    # Check column sums
                    for c in range(j, j + size):
                        if col_sum[c][i+size] - col_sum[c][i] != target:
                            valid = False
                            break
                    
                    if not valid:
                        continue
                    
                    # Check diagonals
                    diag1 = sum(grid[i+k][j+k] for k in range(size))
                    diag2 = sum(grid[i+k][j+size-1-k] for k in range(size))
                    
                    if diag1 == target == diag2:
                        result = size
        
        return result