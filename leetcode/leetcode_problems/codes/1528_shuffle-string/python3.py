"""
Problem: Shuffle String
Difficulty: Easy
Tags: array, string

Approach: Create result array, place each character at its index position
Time Complexity: O(n) where n is length of s
Space Complexity: O(n) for result
"""

class Solution:
    def restoreString(self, s: str, indices: List[int]) -> str:
        result = [''] * len(s)
        for i, idx in enumerate(indices):
            result[idx] = s[i]
        return ''.join(result)