"""
Problem: Construct K Palindrome Strings
Difficulty: Medium
Tags: string, greedy, hash

Approach: Count character frequencies, need at least k palindromes, at most one odd per palindrome
Time Complexity: O(n) where n is length of s
Space Complexity: O(1) for character counts
"""

from collections import Counter

class Solution:
    def canConstruct(self, s: str, k: int) -> bool:
        if len(s) < k:
            return False
        
        freq = Counter(s)
        odd_count = sum(1 for count in freq.values() if count % 2 == 1)
        return odd_count <= k