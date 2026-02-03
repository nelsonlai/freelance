"""
Problem: Substrings of Size Three with Distinct Characters
Difficulty: Easy
Tags: array, string, hash, sliding window

Approach: Sliding window of size 3, check if all characters distinct
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def countGoodSubstrings(self, s: str) -> int:
        if len(s) < 3:
            return 0
        
        count = 0
        for i in range(len(s) - 2):
            substring = s[i:i+3]
            if len(set(substring)) == 3:
                count += 1
        
        return count