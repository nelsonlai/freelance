"""
Problem: Check if Word Equals Summation of Two Words
Difficulty: Easy
Tags: string

Approach: Convert words to numbers, check if sum equals target
Time Complexity: O(n) where n is max word length
Space Complexity: O(1)
"""

class Solution:
    def isSumEqual(self, firstWord: str, secondWord: str, targetWord: str) -> bool:
        def wordToNum(word):
            return int(''.join(str(ord(c) - ord('a')) for c in word))
        
        return wordToNum(firstWord) + wordToNum(secondWord) == wordToNum(targetWord)