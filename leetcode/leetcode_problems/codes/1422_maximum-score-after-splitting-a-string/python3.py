"""
Problem: Maximum Score After Splitting a String
Difficulty: Easy
Tags: array, string, tree

Approach: Try all split positions, count zeros on left and ones on right
Time Complexity: O(n) where n is length of s
Space Complexity: O(1)
"""

class Solution:
    def maxScore(self, s: str) -> int:
        max_score = 0
        for i in range(1, len(s)):
            left_zeros = s[:i].count('0')
            right_ones = s[i:].count('1')
            max_score = max(max_score, left_zeros + right_ones)
        return max_score