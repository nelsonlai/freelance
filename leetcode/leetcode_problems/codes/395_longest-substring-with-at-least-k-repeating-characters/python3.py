"""
Problem: Longest Substring with At Least K Repeating Characters
Difficulty: Medium
Tags: array, string, tree, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

from collections import Counter

class Solution:
    def longestSubstring(self, s: str, k: int) -> int:
        if len(s) < k:
            return 0
        
        count = Counter(s)
        
        for char, freq in count.items():
            if freq < k:
                return max(self.longestSubstring(substring, k) 
                          for substring in s.split(char))
        
        return len(s)