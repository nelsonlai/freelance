"""
Problem: Unique Word Abbreviation
Difficulty: Medium
Tags: array, string, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class ValidWordAbbr:

    def __init__(self, dictionary: List[str]):
        self.abbr_map = defaultdict(set)
        for word in dictionary:
            abbr = self.getAbbr(word)
            self.abbr_map[abbr].add(word)

    def getAbbr(self, word: str) -> str:
        if len(word) <= 2:
            return word
        return word[0] + str(len(word) - 2) + word[-1]

    def isUnique(self, word: str) -> bool:
        abbr = self.getAbbr(word)
        words = self.abbr_map[abbr]
        return len(words) == 0 or (len(words) == 1 and word in words)