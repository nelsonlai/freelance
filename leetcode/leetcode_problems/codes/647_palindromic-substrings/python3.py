"""
Problem: Palindromic Substrings
Difficulty: Medium
Tags: array, string, tree, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def countSubstrings(self, s: str) -> int:
        count = 0
        
        def expand(left, right):
            nonlocal count
            while left >= 0 and right < len(s) and s[left] == s[right]:
                count += 1
                left -= 1
                right += 1
        
        for i in range(len(s)):
            expand(i, i)
            expand(i, i + 1)
        
        return count