"""
Problem: Find All Anagrams in a String
Difficulty: Medium
Tags: array, string, tree, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

from collections import Counter

class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        if len(s) < len(p):
            return []
        
        p_count = Counter(p)
        window_count = Counter(s[:len(p)])
        
        result = []
        if window_count == p_count:
            result.append(0)
        
        for i in range(len(p), len(s)):
            window_count[s[i]] += 1
            window_count[s[i - len(p)]] -= 1
            if window_count[s[i - len(p)]] == 0:
                del window_count[s[i - len(p)]]
            
            if window_count == p_count:
                result.append(i - len(p) + 1)
        
        return result