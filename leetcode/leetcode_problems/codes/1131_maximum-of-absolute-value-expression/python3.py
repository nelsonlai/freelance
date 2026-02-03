"""
Problem: Maximum of Absolute Value Expression
Difficulty: Medium
Tags: array, math

Approach: Expand expression |arr1[i]-arr1[j]| + |arr2[i]-arr2[j]| + |i-j|, try all sign combinations
Time Complexity: O(n) where n is the length of arrays
Space Complexity: O(1)
"""

class Solution:
    def maxAbsValExpr(self, arr1: List[int], arr2: List[int]) -> int:
        # Try all sign combinations: ±(arr1[i]-arr1[j]) ± (arr2[i]-arr2[j]) ± (i-j)
        # This is equivalent to: max over all sign combinations of (arr1[i] ± arr2[i] ± i)
        signs = [(1, 1, 1), (1, 1, -1), (1, -1, 1), (1, -1, -1), 
                 (-1, 1, 1), (-1, 1, -1), (-1, -1, 1), (-1, -1, -1)]
        
        max_val = 0
        for s1, s2, s3 in signs:
            values = [s1 * arr1[i] + s2 * arr2[i] + s3 * i for i in range(len(arr1))]
            max_val = max(max_val, max(values) - min(values))
        
        return max_val