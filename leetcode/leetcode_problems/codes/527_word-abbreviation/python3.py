"""
Problem: Word Abbreviation
Difficulty: Hard
Tags: array, string, greedy, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

from collections import defaultdict

class Solution:
    def wordsAbbreviation(self, words: List[str]) -> List[str]:
        def get_abbrev(word, prefix_len):
            if len(word) <= prefix_len + 2:
                return word
            return word[:prefix_len] + str(len(word) - prefix_len - 1) + word[-1]
        
        n = len(words)
        result = [None] * n
        prefix_len = [1] * n
        
        for i in range(n):
            result[i] = get_abbrev(words[i], prefix_len[i])
        
        for i in range(n):
            while True:
                duplicates = []
                for j in range(i + 1, n):
                    if result[i] == result[j]:
                        duplicates.append(j)
                
                if not duplicates:
                    break
                
                duplicates.append(i)
                for idx in duplicates:
                    prefix_len[idx] += 1
                    result[idx] = get_abbrev(words[idx], prefix_len[idx])
        
        return result