"""
Problem: Implement Magic Dictionary
Difficulty: Medium
Tags: array, string, hash, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class MagicDictionary:
    def __init__(self):
        self.words = set()
        self.count = defaultdict(int)

    def buildDict(self, dictionary: List[str]) -> None:
        self.words = set(dictionary)
        self.count = defaultdict(int)
        for word in dictionary:
            for i in range(len(word)):
                pattern = word[:i] + '*' + word[i+1:]
                self.count[pattern] += 1

    def search(self, searchWord: str) -> bool:
        for i in range(len(searchWord)):
            pattern = searchWord[:i] + '*' + searchWord[i+1:]
            if pattern in self.count:
                if searchWord not in self.words or self.count[pattern] > 1:
                    return True
        return False