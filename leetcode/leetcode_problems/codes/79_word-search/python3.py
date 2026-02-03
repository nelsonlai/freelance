"""
Problem: Word Search
Difficulty: Medium
Tags: array, string, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        m, n = len(board), len(board[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        
        def dfs(row, col, index):
            if index == len(word):
                return True
            
            if row < 0 or row >= m or col < 0 or col >= n:
                return False
            
            if board[row][col] != word[index]:
                return False
            
            temp = board[row][col]
            board[row][col] = '#'
            
            for dr, dc in directions:
                if dfs(row + dr, col + dc, index + 1):
                    return True
            
            board[row][col] = temp
            return False
        
        for i in range(m):
            for j in range(n):
                if dfs(i, j, 0):
                    return True
        
        return False