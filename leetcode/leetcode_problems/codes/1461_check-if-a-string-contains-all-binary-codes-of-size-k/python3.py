"""
Problem: Check If a String Contains All Binary Codes of Size K
Difficulty: Medium
Tags: array, string, tree, hash

Approach: Extract all substrings of length k, check if we have 2^k unique codes
Time Complexity: O(n * k) where n is length of s
Space Complexity: O(2^k) for set
"""

class Solution:
    def hasAllCodes(self, s: str, k: int) -> bool:
        seen = set()
        for i in range(len(s) - k + 1):
            seen.add(s[i:i+k])
        return len(seen) == 2 ** k