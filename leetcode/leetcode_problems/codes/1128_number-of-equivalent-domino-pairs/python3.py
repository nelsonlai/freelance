"""
Problem: Number of Equivalent Domino Pairs
Difficulty: Easy
Tags: array, hash

Approach: Normalize dominoes to (min, max) tuple, count pairs using combination formula
Time Complexity: O(n) where n is the number of dominoes
Space Complexity: O(n) for frequency map
"""

class Solution:
    def numEquivDominoPairs(self, dominoes: List[List[int]]) -> int:
        from collections import Counter
        normalized = []
        for a, b in dominoes:
            normalized.append((min(a, b), max(a, b)))
        
        freq = Counter(normalized)
        count = 0
        for cnt in freq.values():
            count += cnt * (cnt - 1) // 2
        
        return count