"""
Problem: Find K-Length Substrings With No Repeated Characters
Difficulty: Medium
Tags: array, string, tree, hash

Approach: Sliding window - maintain window of size k with no duplicates
Time Complexity: O(n) where n is string length
Space Complexity: O(k) for character set
"""

class Solution:
    def numKLenSubstrNoRepeats(self, s: str, k: int) -> int:
        if len(s) < k:
            return 0
        
        char_count = {}
        result = 0
        
        for i in range(k):
            char_count[s[i]] = char_count.get(s[i], 0) + 1
        
        if len(char_count) == k:
            result += 1
        
        for i in range(k, len(s)):
            char_count[s[i]] = char_count.get(s[i], 0) + 1
            char_count[s[i - k]] -= 1
            if char_count[s[i - k]] == 0:
                del char_count[s[i - k]]
            
            if len(char_count) == k:
                result += 1
        
        return result