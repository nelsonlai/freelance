"""
Problem: Minimum Number of Steps to Make Two Strings Anagram
Difficulty: Medium
Tags: string, hash

Approach: Count character frequencies, sum positive differences
Time Complexity: O(n) where n is length of strings
Space Complexity: O(1) for frequency arrays
"""

from collections import Counter

class Solution:
    def minSteps(self, s: str, t: str) -> int:
        count_s = Counter(s)
        count_t = Counter(t)
        
        steps = 0
        for char in count_s:
            if count_s[char] > count_t.get(char, 0):
                steps += count_s[char] - count_t.get(char, 0)
        
        return steps