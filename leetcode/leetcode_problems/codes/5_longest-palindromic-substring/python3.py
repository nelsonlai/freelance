"""
Problem: Longest Palindromic Substring
Difficulty: Medium
Tags: array, string, tree, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def longestPalindrome(self, s: str) -> str:
        def expand_around_center(left: int, right: int) -> str:
            while left >= 0 and right < len(s) and s[left] == s[right]:
                left -= 1
                right += 1
            return s[left + 1:right]
        
        if not s:
            return ""
        
        longest = ""
        for i in range(len(s)):
            # Odd length palindromes
            palindrome1 = expand_around_center(i, i)
            # Even length palindromes
            palindrome2 = expand_around_center(i, i + 1)
            
            longest = max(longest, palindrome1, palindrome2, key=len)
        
        return longest