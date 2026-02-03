"""
Problem: Reverse Words in a String II
Difficulty: Medium
Tags: array, string

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def reverseWords(self, s: List[str]) -> None:
        def reverse(start, end):
            while start < end:
                s[start], s[end] = s[end], s[start]
                start += 1
                end -= 1
        
        reverse(0, len(s) - 1)
        
        start = 0
        for i in range(len(s)):
            if s[i] == ' ':
                reverse(start, i - 1)
                start = i + 1
        reverse(start, len(s) - 1)