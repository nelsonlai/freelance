"""
Problem: Shortest Palindrome
Difficulty: Hard
Tags: string, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def shortestPalindrome(self, s: str) -> str:
        if not s:
            return s
        
        rev = s[::-1]
        for i in range(len(s)):
            if s[:len(s) - i] == rev[i:]:
                return rev[:i] + s
        return rev + s