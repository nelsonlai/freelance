"""
Problem: String Matching in an Array
Difficulty: Easy
Tags: array, string, tree

Approach: Check if each word is substring of any other word
Time Complexity: O(n^2 * m) where n is words, m is average length
Space Complexity: O(n) for result
"""

class Solution:
    def stringMatching(self, words: List[str]) -> List[str]:
        result = []
        for i, word in enumerate(words):
            for j, other in enumerate(words):
                if i != j and word in other:
                    result.append(word)
                    break
        return result