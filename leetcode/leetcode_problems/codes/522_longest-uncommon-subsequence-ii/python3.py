"""
Problem: Longest Uncommon Subsequence II
Difficulty: Medium
Tags: array, string, hash, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def findLUSlength(self, strs: List[str]) -> int:
        def is_subsequence(s, t):
            i = 0
            for char in t:
                if i < len(s) and s[i] == char:
                    i += 1
            return i == len(s)
        
        strs.sort(key=len, reverse=True)
        
        for i, s in enumerate(strs):
            is_uncommon = True
            for j, t in enumerate(strs):
                if i != j and is_subsequence(s, t):
                    is_uncommon = False
                    break
            if is_uncommon:
                return len(s)
        
        return -1