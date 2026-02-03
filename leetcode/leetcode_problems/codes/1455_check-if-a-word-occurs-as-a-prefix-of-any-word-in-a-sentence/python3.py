"""
Problem: Check If a Word Occurs As a Prefix of Any Word in a Sentence
Difficulty: Easy
Tags: array, string, tree, search

Approach: Split sentence, check if searchWord is prefix of any word
Time Complexity: O(n * m) where n is words, m is searchWord length
Space Complexity: O(n) for words
"""

class Solution:
    def isPrefixOfWord(self, sentence: str, searchWord: str) -> int:
        words = sentence.split()
        for i, word in enumerate(words):
            if word.startswith(searchWord):
                return i + 1
        return -1