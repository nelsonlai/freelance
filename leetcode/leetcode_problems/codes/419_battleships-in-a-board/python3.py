"""
Problem: Battleships in a Board
Difficulty: Medium
Tags: array, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def countBattleships(self, board: List[List[str]]) -> int:
        count = 0
        m, n = len(board), len(board[0])
        
        for i in range(m):
            for j in range(n):
                if board[i][j] == 'X':
                    if (i == 0 or board[i-1][j] != 'X') and (j == 0 or board[i][j-1] != 'X'):
                        count += 1
        
        return count