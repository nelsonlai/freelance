"""
Problem: Break a Palindrome
Difficulty: Medium
Tags: string, graph, greedy

Approach: Replace first non-'a' with 'a', or if all 'a', replace last char with 'b'
Time Complexity: O(n) where n is length of palindrome
Space Complexity: O(n) for result
"""

class Solution:
    def breakPalindrome(self, palindrome: str) -> str:
        if len(palindrome) == 1:
            return ""
        
        s = list(palindrome)
        for i in range(len(s) // 2):
            if s[i] != 'a':
                s[i] = 'a'
                return ''.join(s)
        
        s[-1] = 'b'
        return ''.join(s)