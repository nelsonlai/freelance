"""
Problem: Find Common Characters
Difficulty: Easy
Tags: array, string, hash

Approach: Find minimum count of each character across all words
Time Complexity: O(n * m) where n is number of words, m is average length
Space Complexity: O(1) for character counts
"""

from collections import Counter

class Solution:
    def commonChars(self, words: List[str]) -> List[str]:
        min_count = Counter(words[0])
        
        for word in words[1:]:
            word_count = Counter(word)
            for char in min_count:
                min_count[char] = min(min_count[char], word_count.get(char, 0))
        
        result = []
        for char, count in min_count.items():
            result.extend([char] * count)
        
        return result