"""
Problem: Longest Common Subsequence Between Sorted Arrays
Difficulty: Medium
Tags: array, hash, sort, two pointers

Approach: Count frequency, return elements appearing in all arrays
Time Complexity: O(n * m) where n is arrays, m is avg length
Space Complexity: O(m)
"""

from collections import Counter

class Solution:
    def longestCommonSubsequence(self, arrays: List[List[int]]) -> List[int]:
        count = Counter()
        for arr in arrays:
            count.update(set(arr))
        
        n = len(arrays)
        return sorted([num for num, cnt in count.items() if cnt == n])