"""
Problem: Longest Repeating Character Replacement
Difficulty: Medium
Tags: array, string, tree, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

from collections import defaultdict

class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        count = defaultdict(int)
        max_count = 0
        max_length = 0
        left = 0
        
        for right in range(len(s)):
            count[s[right]] += 1
            max_count = max(max_count, count[s[right]])
            
            if right - left + 1 - max_count > k:
                count[s[left]] -= 1
                left += 1
            
            max_length = max(max_length, right - left + 1)
        
        return max_length