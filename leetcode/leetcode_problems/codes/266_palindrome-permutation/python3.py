"""
Problem: Palindrome Permutation
Difficulty: Easy
Tags: string, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def canPermutePalindrome(self, s: str) -> bool:
        count = Counter(s)
        odd_count = sum(1 for v in count.values() if v % 2 == 1)
        return odd_count <= 1