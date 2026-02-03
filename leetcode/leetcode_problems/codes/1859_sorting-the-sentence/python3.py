"""
Problem: Sorting the Sentence
Difficulty: Easy
Tags: string, sort

Approach: Split words, extract position numbers, sort and reconstruct
Time Complexity: O(n log n) where n is words
Space Complexity: O(n)
"""

class Solution:
    def sortSentence(self, s: str) -> str:
        words = s.split()
        words.sort(key=lambda x: int(x[-1]))
        return ' '.join(word[:-1] for word in words)