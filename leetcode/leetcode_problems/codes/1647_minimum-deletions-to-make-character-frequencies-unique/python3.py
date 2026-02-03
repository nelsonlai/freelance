"""
Problem: Minimum Deletions to Make Character Frequencies Unique
Difficulty: Medium
Tags: string, greedy, hash, sort

Approach: Count frequencies, sort descending, for each frequency, reduce to next available unique value
Time Complexity: O(n + k log k) where k is unique characters
Space Complexity: O(k) for frequency map
"""

from collections import Counter

class Solution:
    def minDeletions(self, s: str) -> int:
        freq = Counter(s)
        frequencies = sorted(freq.values(), reverse=True)
        
        deletions = 0
        seen = set()
        
        for f in frequencies:
            while f > 0 and f in seen:
                f -= 1
                deletions += 1
            seen.add(f)
        
        return deletions