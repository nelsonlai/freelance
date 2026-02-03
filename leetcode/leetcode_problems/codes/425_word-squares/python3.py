"""
Problem: Word Squares
Difficulty: Hard
Tags: array, string

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

from collections import defaultdict

class Solution:
    def wordSquares(self, words: List[str]) -> List[List[str]]:
        n = len(words[0])
        prefix_map = defaultdict(list)
        
        for word in words:
            for i in range(n):
                prefix_map[word[:i+1]].append(word)
        
        result = []
        
        def backtrack(square):
            if len(square) == n:
                result.append(square[:])
                return
            
            prefix = ''.join(word[len(square)] for word in square)
            for word in prefix_map[prefix]:
                backtrack(square + [word])
        
        for word in words:
            backtrack([word])
        
        return result