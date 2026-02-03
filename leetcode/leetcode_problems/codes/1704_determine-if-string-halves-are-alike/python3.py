"""
Problem: Determine if String Halves Are Alike
Difficulty: Easy
Tags: string

Approach: Count vowels in first and second half, compare
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def halvesAreAlike(self, s: str) -> bool:
        vowels = set('aeiouAEIOU')
        n = len(s)
        mid = n // 2
        
        first_half = sum(1 for c in s[:mid] if c in vowels)
        second_half = sum(1 for c in s[mid:] if c in vowels)
        
        return first_half == second_half