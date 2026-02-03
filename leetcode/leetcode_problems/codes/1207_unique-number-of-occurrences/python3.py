"""
Problem: Unique Number of Occurrences
Difficulty: Easy
Tags: array, hash

Approach: Count frequencies, check if all frequencies are unique
Time Complexity: O(n) where n is the length of arr
Space Complexity: O(n) for frequency map
"""

from collections import Counter

class Solution:
    def uniqueOccurrences(self, arr: List[int]) -> bool:
        freq = Counter(arr)
        occurrences = freq.values()
        return len(occurrences) == len(set(occurrences))