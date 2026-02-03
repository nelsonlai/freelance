"""
Problem: Rearrange Words in a Sentence
Difficulty: Medium
Tags: string, sort

Approach: Split, sort by length, capitalize first word, lowercase rest
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for words list
"""

class Solution:
    def arrangeWords(self, text: str) -> str:
        words = text.split()
        words.sort(key=len)
        result = ' '.join(words)
        return result[0].upper() + result[1:].lower()