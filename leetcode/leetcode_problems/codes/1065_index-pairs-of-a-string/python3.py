"""
Problem: Index Pairs of a String
Difficulty: Easy
Tags: array, string, tree, sort

Approach: For each word, find all occurrences in text
Time Complexity: O(n * m * k) where n is text length, m is words, k is word length
Space Complexity: O(1) excluding output
"""

class Solution:
    def indexPairs(self, text: str, words: List[str]) -> List[List[int]]:
        result = []
        for word in words:
            start = 0
            while True:
                idx = text.find(word, start)
                if idx == -1:
                    break
                result.append([idx, idx + len(word) - 1])
                start = idx + 1
        
        result.sort()
        return result