"""
Problem: Word Break II
Difficulty: Hard
Tags: array, string, dp, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

from functools import lru_cache

class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        wordSet = set(wordDict)
        
        @lru_cache(maxsize=None)
        def backtrack(start):
            if start == len(s):
                return [""]
            
            result = []
            for end in range(start + 1, len(s) + 1):
                word = s[start:end]
                if word in wordSet:
                    for sentence in backtrack(end):
                        if sentence:
                            result.append(word + " " + sentence)
                        else:
                            result.append(word)
            return result
        
        return backtrack(0)