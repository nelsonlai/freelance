"""
Problem: Find Words That Can Be Formed by Characters
Difficulty: Easy
Tags: array, string, tree, hash

Approach: Count character frequencies in chars, check if each word can be formed
Time Complexity: O(n * m) where n is number of words, m is average word length
Space Complexity: O(1) since at most 26 characters
"""

class Solution:
    def countCharacters(self, words: List[str], chars: str) -> int:
        from collections import Counter
        
        char_count = Counter(chars)
        total_length = 0
        
        for word in words:
            word_count = Counter(word)
            if all(word_count[char] <= char_count.get(char, 0) for char in word_count):
                total_length += len(word)
        
        return total_length