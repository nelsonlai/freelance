"""
Problem: Number of Valid Words in a Sentence
Difficulty: Easy
Tags: string

Approach: Check each word against validation rules
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

import re

class Solution:
    def countValidWords(self, sentence: str) -> int:
        words = sentence.split()
        count = 0
        
        for word in words:
            if self.isValid(word):
                count += 1
        
        return count
    
    def isValid(self, word: str) -> bool:
        # Check for digits
        if any(c.isdigit() for c in word):
            return False
        
        # Count hyphens and punctuation
        hyphen_count = word.count('-')
        punct_count = sum(1 for c in word if c in '!.,')
        
        if hyphen_count > 1 or punct_count > 1:
            return False
        
        # Hyphen must be between letters
        if '-' in word:
            idx = word.index('-')
            if idx == 0 or idx == len(word) - 1:
                return False
            if not word[idx - 1].isalpha() or not word[idx + 1].isalpha():
                return False
        
        # Punctuation must be at the end
        for c in '!.,':
            if c in word and word[-1] != c:
                return False
        
        return True