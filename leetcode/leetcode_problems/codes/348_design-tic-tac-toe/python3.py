"""
Problem: Design Tic-Tac-Toe
Difficulty: Medium
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class TicTacToe:

    def __init__(self, n: int):
        self.n = n
        self.rows = [0] * n
        self.cols = [0] * n
        self.diag = 0
        self.anti_diag = 0

    def move(self, row: int, col: int, player: int) -> int:
        value = 1 if player == 1 else -1
        
        self.rows[row] += value
        self.cols[col] += value
        
        if row == col:
            self.diag += value
        if row + col == self.n - 1:
            self.anti_diag += value
        
        if abs(self.rows[row]) == self.n or abs(self.cols[col]) == self.n or \
           abs(self.diag) == self.n or abs(self.anti_diag) == self.n:
            return player
        
        return 0