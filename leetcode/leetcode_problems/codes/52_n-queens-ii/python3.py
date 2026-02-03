"""
Problem: N-Queens II
Difficulty: Hard
Tags: general

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def totalNQueens(self, n: int) -> int:
        count = 0
        cols = set()
        diag1 = set()
        diag2 = set()
        
        def backtrack(row):
            nonlocal count
            if row == n:
                count += 1
                return
            
            for col in range(n):
                if col in cols or (row - col) in diag1 or (row + col) in diag2:
                    continue
                
                cols.add(col)
                diag1.add(row - col)
                diag2.add(row + col)
                
                backtrack(row + 1)
                
                cols.remove(col)
                diag1.remove(row - col)
                diag2.remove(row + col)
        
        backtrack(0)
        return count