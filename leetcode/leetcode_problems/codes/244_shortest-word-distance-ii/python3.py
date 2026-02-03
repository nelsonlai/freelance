"""
Problem: Shortest Word Distance II
Difficulty: Medium
Tags: array, string, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class WordDistance:

    def __init__(self, wordsDict: List[str]):
        self.word_indices = defaultdict(list)
        for i, word in enumerate(wordsDict):
            self.word_indices[word].append(i)

    def shortest(self, word1: str, word2: str) -> int:
        indices1 = self.word_indices[word1]
        indices2 = self.word_indices[word2]
        
        i = j = 0
        min_distance = float('inf')
        
        while i < len(indices1) and j < len(indices2):
            min_distance = min(min_distance, abs(indices1[i] - indices2[j]))
            if indices1[i] < indices2[j]:
                i += 1
            else:
                j += 1
        
        return min_distance