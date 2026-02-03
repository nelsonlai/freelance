"""
Problem: Merge Strings Alternately
Difficulty: Easy
Tags: array, string, two pointers

Approach: Alternate characters from both strings
Time Complexity: O(n + m) where n, m are lengths
Space Complexity: O(n + m)
"""

class Solution:
    def mergeAlternately(self, word1: str, word2: str) -> str:
        result = []
        i, j = 0, 0
        
        while i < len(word1) and j < len(word2):
            result.append(word1[i])
            result.append(word2[j])
            i += 1
            j += 1
        
        result.extend(word1[i:])
        result.extend(word2[j:])
        
        return ''.join(result)