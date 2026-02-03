"""
Problem: Word Search II
Difficulty: Hard
Tags: array, string, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class TrieNode:
    def __init__(self):
        self.children = {}
        self.word = None

class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        root = TrieNode()
        for word in words:
            node = root
            for char in word:
                if char not in node.children:
                    node.children[char] = TrieNode()
                node = node.children[char]
            node.word = word
        
        result = []
        m, n = len(board), len(board[0])
        
        def dfs(i, j, node):
            char = board[i][j]
            curr_node = node.children[char]
            
            if curr_node.word:
                result.append(curr_node.word)
                curr_node.word = None
            
            board[i][j] = '#'
            for di, dj in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and board[ni][nj] in curr_node.children:
                    dfs(ni, nj, curr_node)
            board[i][j] = char
            
            if not curr_node.children:
                del node.children[char]
        
        for i in range(m):
            for j in range(n):
                if board[i][j] in root.children:
                    dfs(i, j, root)
        
        return result