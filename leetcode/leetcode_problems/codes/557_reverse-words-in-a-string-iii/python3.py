"""
Problem: Reverse Words in a String III
Difficulty: Easy
Tags: array, string

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def reverseWords(self, s: str) -> str:
        words = s.split()
        return ' '.join(word[::-1] for word in words)