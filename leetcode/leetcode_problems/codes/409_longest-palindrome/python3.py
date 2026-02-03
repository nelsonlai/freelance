"""
Problem: Longest Palindrome
Difficulty: Easy
Tags: string, greedy, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def longestPalindrome(self, s: str) -> int:
        count = Counter(s)
        length = 0
        has_odd = False
        
        for freq in count.values():
            length += (freq // 2) * 2
            if freq % 2 == 1:
                has_odd = True
        
        return length + (1 if has_odd else 0)