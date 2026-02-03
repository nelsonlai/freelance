"""
Problem: Length of Last Word
Difficulty: Easy
Tags: string, tree

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def lengthOfLastWord(self, s: str) -> int:
        s = s.rstrip()
        length = 0
        for i in range(len(s) - 1, -1, -1):
            if s[i] == ' ':
                break
            length += 1
        return length