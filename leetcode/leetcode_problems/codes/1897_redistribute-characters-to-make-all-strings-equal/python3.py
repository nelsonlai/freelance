"""
Problem: Redistribute Characters to Make All Strings Equal
Difficulty: Easy
Tags: array, string, hash

Approach: Count all characters, check if divisible by number of words
Time Complexity: O(n * m) where n is words, m is avg length
Space Complexity: O(1) - fixed 26 characters
"""

from collections import Counter

class Solution:
    def makeEqual(self, words: List[str]) -> bool:
        count = Counter()
        for word in words:
            count.update(word)
        
        n = len(words)
        for char_count in count.values():
            if char_count % n != 0:
                return False
        
        return True