"""
Problem: Find the Index of the First Occurrence in a String
Difficulty: Easy
Tags: array, string, stack

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        if not needle:
            return 0
        
        n = len(haystack)
        m = len(needle)
        
        for i in range(n - m + 1):
            if haystack[i:i + m] == needle:
                return i
        
        return -1