"""
Problem: Flip Columns For Maximum Number of Equal Rows
Difficulty: Medium
Tags: array, hash

Approach: Count rows with same pattern (original or flipped)
Time Complexity: O(m * n) where m and n are dimensions
Space Complexity: O(m * n) for patterns
"""

from collections import Counter

class Solution:
    def maxEqualRowsAfterFlips(self, matrix: List[List[int]]) -> int:
        patterns = Counter()
        
        for row in matrix:
            pattern1 = tuple(row)
            pattern2 = tuple(1 - x for x in row)
            patterns[pattern1] += 1
            patterns[pattern2] += 1
        
        return max(patterns.values()) // 2