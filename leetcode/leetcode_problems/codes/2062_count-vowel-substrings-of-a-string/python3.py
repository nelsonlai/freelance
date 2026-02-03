"""
Problem: Count Vowel Substrings of a String
Difficulty: Easy
Tags: string, hash, sliding window

Approach: Count substrings containing all 5 vowels exactly once each
Time Complexity: O(n^2) where n is string length
Space Complexity: O(1)
"""

from collections import Counter

class Solution:
    def countVowelSubstrings(self, word: str) -> int:
        vowels = {'a', 'e', 'i', 'o', 'u'}
        result = 0
        n = len(word)
        
        for i in range(n):
            count = Counter()
            for j in range(i, n):
                if word[j] not in vowels:
                    break
                count[word[j]] += 1
                if len(count) == 5 and all(count[v] == 1 for v in vowels):
                    result += 1
        
        return result