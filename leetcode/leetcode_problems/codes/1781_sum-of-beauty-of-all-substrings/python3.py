"""
Problem: Sum of Beauty of All Substrings
Difficulty: Medium
Tags: string, hash

Approach: For each substring, count frequencies, beauty = max_freq - min_freq
Time Complexity: O(n^2) where n is length
Space Complexity: O(1) for frequency counter
"""

from collections import Counter

class Solution:
    def beautySum(self, s: str) -> int:
        result = 0
        n = len(s)
        
        for i in range(n):
            freq = Counter()
            for j in range(i, n):
                freq[s[j]] += 1
                if len(freq) > 1:
                    result += max(freq.values()) - min(freq.values())
        
        return result