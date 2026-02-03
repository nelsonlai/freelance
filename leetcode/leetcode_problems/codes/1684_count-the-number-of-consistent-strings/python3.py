"""
Problem: Count the Number of Consistent Strings
Difficulty: Easy
Tags: array, string, hash

Approach: Check if all characters in each word are in allowed set
Time Complexity: O(n * m) where n is words, m is word length
Space Complexity: O(1) for character set
"""

class Solution:
    def countConsistentStrings(self, allowed: str, words: List[str]) -> int:
        allowed_set = set(allowed)
        result = 0
        
        for word in words:
            if all(char in allowed_set for char in word):
                result += 1
        
        return result