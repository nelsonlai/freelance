"""
Problem: Find the Longest Substring Containing Vowels in Even Counts
Difficulty: Medium
Tags: array, string, tree, hash

Approach: Use bitmask to track vowel parity, find longest substring with same mask
Time Complexity: O(n) where n is length of s
Space Complexity: O(1) for mask map
"""

class Solution:
    def findTheLongestSubstring(self, s: str) -> int:
        vowel_map = {'a': 0, 'e': 1, 'i': 2, 'o': 3, 'u': 4}
        mask_map = {0: -1}
        mask = 0
        max_len = 0
        
        for i, char in enumerate(s):
            if char in vowel_map:
                mask ^= 1 << vowel_map[char]
            
            if mask in mask_map:
                max_len = max(max_len, i - mask_map[mask])
            else:
                mask_map[mask] = i
        
        return max_len