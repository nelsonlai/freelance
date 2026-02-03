"""
Problem: Split Two Strings to Make Palindrome
Difficulty: Medium
Tags: array, string, two pointers

Approach: Try splitting at different positions, check if prefix of one + suffix of other forms palindrome
Time Complexity: O(n) where n is length of strings
Space Complexity: O(1)
"""

class Solution:
    def checkPalindromeFormation(self, a: str, b: str) -> bool:
        def is_palindrome(s, i, j):
            while i < j:
                if s[i] != s[j]:
                    return False
                i += 1
                j -= 1
            return True
        
        def check(a, b):
            i, j = 0, len(a) - 1
            while i < j and a[i] == b[j]:
                i += 1
                j -= 1
            return is_palindrome(a, i, j) or is_palindrome(b, i, j)
        
        return check(a, b) or check(b, a)