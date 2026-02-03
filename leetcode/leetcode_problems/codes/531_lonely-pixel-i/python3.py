"""
Problem: Lonely Pixel I
Difficulty: Medium
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def findLonelyPixel(self, picture: List[List[str]]) -> int:
        m, n = len(picture), len(picture[0])
        row_count = defaultdict(int)
        col_count = defaultdict(int)
        
        for i in range(m):
            for j in range(n):
                if picture[i][j] == 'B':
                    row_count[i] += 1
                    col_count[j] += 1
        
        result = 0
        for i in range(m):
            for j in range(n):
                if picture[i][j] == 'B' and row_count[i] == 1 and col_count[j] == 1:
                    result += 1
        
        return result