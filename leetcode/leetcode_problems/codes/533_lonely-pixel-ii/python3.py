"""
Problem: Lonely Pixel II
Difficulty: Medium
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def findBlackPixel(self, picture: List[List[str]], target: int) -> int:
        m, n = len(picture), len(picture[0])
        row_count = defaultdict(int)
        col_count = defaultdict(int)
        row_patterns = defaultdict(int)
        
        for i in range(m):
            pattern = ''.join(picture[i])
            row_patterns[pattern] += 1
            for j in range(n):
                if picture[i][j] == 'B':
                    row_count[i] += 1
                    col_count[j] += 1
        
        result = 0
        for j in range(n):
            if col_count[j] == target:
                for i in range(m):
                    if picture[i][j] == 'B':
                        pattern = ''.join(picture[i])
                        if row_count[i] == target and row_patterns[pattern] == target:
                            result += 1
                        break
        
        return result