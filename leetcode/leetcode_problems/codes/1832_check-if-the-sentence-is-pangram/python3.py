"""
Problem: Check if the Sentence Is Pangram
Difficulty: Easy
Tags: string, hash

Approach: Check if all 26 letters are present
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def checkIfPangram(self, sentence: str) -> bool:
        return len(set(sentence)) == 26