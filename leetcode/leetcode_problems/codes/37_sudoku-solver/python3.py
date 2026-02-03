"""
Problem: Sudoku Solver
Difficulty: Hard
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def solveSudoku(self, board: List[List[str]]) -> None:
        def isValid(row, col, num):
            for i in range(9):
                if board[row][i] == num or board[i][col] == num:
                    return False
                if board[3 * (row // 3) + i // 3][3 * (col // 3) + i % 3] == num:
                    return False
            return True
        
        def solve():
            for i in range(9):
                for j in range(9):
                    if board[i][j] == '.':
                        for num in '123456789':
                            if isValid(i, j, num):
                                board[i][j] = num
                                if solve():
                                    return True
                                board[i][j] = '.'
                        return False
            return True
        
        solve()