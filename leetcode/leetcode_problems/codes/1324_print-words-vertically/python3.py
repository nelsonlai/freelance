"""
Problem: Print Words Vertically
Difficulty: Medium
Tags: array, string

Approach: Split words, find max length, pad shorter words, transpose
Time Complexity: O(n * m) where n is words, m is max length
Space Complexity: O(n * m) for result
"""

class Solution:
    def printVertically(self, s: str) -> List[str]:
        words = s.split()
        max_len = max(len(word) for word in words)
        result = []
        
        for i in range(max_len):
            col = []
            for word in words:
                col.append(word[i] if i < len(word) else ' ')
            result.append(''.join(col).rstrip())
        
        return result