"""
Problem: Can Convert String in K Moves
Difficulty: Medium
Tags: string, hash

Approach: For each position, calculate required shift, track if shift is available within k moves
Time Complexity: O(n) where n is length of strings
Space Complexity: O(26) for shift counts
"""

from collections import Counter

class Solution:
    def canConvertString(self, s: str, t: str, k: int) -> bool:
        if len(s) != len(t):
            return False
        
        shifts = Counter()
        for i in range(len(s)):
            shift = (ord(t[i]) - ord(s[i])) % 26
            if shift > 0:
                shifts[shift] += 1
        
        for shift, count in shifts.items():
            max_shift = shift + 26 * (count - 1)
            if max_shift > k:
                return False
        
        return True