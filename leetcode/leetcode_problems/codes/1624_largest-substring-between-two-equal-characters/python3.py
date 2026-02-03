"""
Problem: Largest Substring Between Two Equal Characters
Difficulty: Easy
Tags: string, hash

Approach: Track first and last occurrence of each character, find max distance
Time Complexity: O(n) where n is length of s
Space Complexity: O(1) for character set
"""

class Solution:
    def maxLengthBetweenEqualCharacters(self, s: str) -> int:
        first_occurrence = {}
        max_length = -1
        
        for i, char in enumerate(s):
            if char in first_occurrence:
                max_length = max(max_length, i - first_occurrence[char] - 1)
            else:
                first_occurrence[char] = i
        
        return max_length