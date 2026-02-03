"""
Problem: Concatenated Words
Difficulty: Hard
Tags: array, string, dp, sort, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
        word_set = set(words)
        result = []
        
        def can_form(word):
            if not word:
                return False
            dp = [False] * (len(word) + 1)
            dp[0] = True
            
            for i in range(1, len(word) + 1):
                for j in range(i):
                    if dp[j] and word[j:i] in word_set:
                        dp[i] = True
                        break
            return dp[len(word)]
        
        for word in words:
            word_set.remove(word)
            if can_form(word):
                result.append(word)
            word_set.add(word)
        
        return result