"""
Problem: Maximum Number of Occurrences of a Substring
Difficulty: Medium
Tags: array, string, tree, hash

Approach: Only need to check minSize (if longer substring appears, shorter also appears)
Time Complexity: O(n * minSize) where n is length of s
Space Complexity: O(n) for substring counts
"""

from collections import Counter

class Solution:
    def maxFreq(self, s: str, maxLetters: int, minSize: int, maxSize: int) -> int:
        substring_count = Counter()
        
        for i in range(len(s) - minSize + 1):
            substring = s[i:i + minSize]
            if len(set(substring)) <= maxLetters:
                substring_count[substring] += 1
        
        return max(substring_count.values()) if substring_count else 0