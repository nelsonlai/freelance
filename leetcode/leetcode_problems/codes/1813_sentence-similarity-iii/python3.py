"""
Problem: Sentence Similarity III
Difficulty: Medium
Tags: array, string, two pointers

Approach: Check if one sentence can be formed by adding words to the other
Time Complexity: O(n + m) where n, m are sentence lengths
Space Complexity: O(n + m)
"""

class Solution:
    def areSentencesSimilar(self, sentence1: str, sentence2: str) -> bool:
        words1 = sentence1.split()
        words2 = sentence2.split()
        
        if len(words1) < len(words2):
            words1, words2 = words2, words1
        
        # Check prefix
        i = 0
        while i < len(words2) and words1[i] == words2[i]:
            i += 1
        
        # Check suffix
        j = 0
        while j < len(words2) and words1[len(words1) - 1 - j] == words2[len(words2) - 1 - j]:
            j += 1
        
        return i + j >= len(words2)