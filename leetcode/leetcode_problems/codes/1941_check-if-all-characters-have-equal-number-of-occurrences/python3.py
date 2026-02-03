"""
Problem: Check if All Characters Have Equal Number of Occurrences
Difficulty: Easy
Tags: string, hash

Approach: Count occurrences, check if all equal
Time Complexity: O(n) where n is length
Space Complexity: O(1) - fixed 26 characters
"""

from collections import Counter

class Solution:
    def areOccurrencesEqual(self, s: str) -> bool:
        count = Counter(s)
        values = list(count.values())
        return len(set(values)) == 1