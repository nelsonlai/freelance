"""
Problem: Number of Equal Count Substrings
Difficulty: Medium
Tags: array, string, hash, sliding window

Approach: For each character, find substrings where all characters appear exactly 'count' times
Time Complexity: O(n * 26) where n is string length
Space Complexity: O(26)
"""

from collections import Counter

class Solution:
    def equalCountSubstrings(self, s: str, count: int) -> int:
        result = 0
        n = len(s)
        
        for i in range(n):
            char_count = Counter()
            for j in range(i, n):
                char_count[s[j]] += 1
                
                # Check if all characters in current substring appear exactly 'count' times
                valid = True
                for c in char_count:
                    if char_count[c] != count and char_count[c] != 0:
                        valid = False
                        break
                
                if valid and all(char_count[c] == count for c in char_count if char_count[c] > 0):
                    result += 1
        
        return result