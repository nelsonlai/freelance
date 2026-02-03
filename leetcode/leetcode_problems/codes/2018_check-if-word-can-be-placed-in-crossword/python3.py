"""
Problem: Check if Word Can Be Placed In Crossword
Difficulty: Medium
Tags: array, string

Approach: Check all horizontal and vertical spaces, try placing word forward and backward
Time Complexity: O(m * n * len(word)) where m, n are board dimensions
Space Complexity: O(1)
"""

class Solution:
    def placeWordInCrossword(self, board: List[List[str]], word: str) -> bool:
        m, n = len(board), len(board[0])
        word_len = len(word)
        
        # Check horizontal spaces
        for i in range(m):
            j = 0
            while j < n:
                if board[i][j] == '#':
                    j += 1
                    continue
                
                start = j
                while j < n and board[i][j] != '#':
                    j += 1
                
                space_len = j - start
                if space_len == word_len:
                    # Try forward
                    if self.canPlace(board, i, start, 0, 1, word):
                        return True
                    # Try backward
                    if self.canPlace(board, i, start + word_len - 1, 0, -1, word):
                        return True
        
        # Check vertical spaces
        for j in range(n):
            i = 0
            while i < m:
                if board[i][j] == '#':
                    i += 1
                    continue
                
                start = i
                while i < m and board[i][j] != '#':
                    i += 1
                
                space_len = i - start
                if space_len == word_len:
                    # Try forward
                    if self.canPlace(board, start, j, 1, 0, word):
                        return True
                    # Try backward
                    if self.canPlace(board, start + word_len - 1, j, -1, 0, word):
                        return True
        
        return False
    
    def canPlace(self, board, i, j, di, dj, word):
        for idx, char in enumerate(word):
            ni, nj = i + di * idx, j + dj * idx
            if board[ni][nj] != ' ' and board[ni][nj] != char:
                return False
        return True