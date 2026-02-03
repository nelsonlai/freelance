"""
Problem: Number of Distinct Substrings in a String
Difficulty: Medium
Tags: array, string, hash, trie

Approach: Generate all substrings, use set to count distinct ones
Time Complexity: O(n^2) where n is length
Space Complexity: O(n^2) for all substrings
"""

class Solution:
    def countDistinct(self, s: str) -> int:
        distinct = set()
        n = len(s)
        
        for i in range(n):
            for j in range(i + 1, n + 1):
                distinct.add(s[i:j])
        
        return len(distinct)