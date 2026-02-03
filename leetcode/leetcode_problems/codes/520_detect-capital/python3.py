"""
Problem: Detect Capital
Difficulty: Easy
Tags: string

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def detectCapitalUse(self, word: str) -> bool:
        if len(word) <= 1:
            return True
        
        if word[0].isupper():
            return all(c.isupper() for c in word[1:]) or all(c.islower() for c in word[1:])
        else:
            return all(c.islower() for c in word[1:])