"""
Problem: Maximum Number of Words You Can Type
Difficulty: Easy
Tags: string, hash

Approach: Check each word if contains any broken letter
Time Complexity: O(n * m) where n is words, m is avg word length
Space Complexity: O(1) - fixed 26 characters
"""

class Solution:
    def canBeTypedWords(self, text: str, brokenLetters: str) -> int:
        broken = set(brokenLetters)
        words = text.split()
        count = 0
        
        for word in words:
            if not any(c in broken for c in word):
                count += 1
        
        return count