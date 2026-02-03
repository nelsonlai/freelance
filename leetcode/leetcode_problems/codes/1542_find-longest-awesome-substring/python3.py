"""
Problem: Find Longest Awesome Substring
Difficulty: Hard
Tags: string, tree, hash

Approach: Use bitmask to track digit parity, find longest substring with at most one odd count
Time Complexity: O(n * 10) where n is length of s
Space Complexity: O(2^10) for mask map
"""

class Solution:
    def longestAwesome(self, s: str) -> int:
        mask_map = {0: -1}
        mask = 0
        max_len = 0
        
        for i, char in enumerate(s):
            digit = int(char)
            mask ^= 1 << digit
            
            if mask in mask_map:
                max_len = max(max_len, i - mask_map[mask])
            else:
                mask_map[mask] = i
            
            for j in range(10):
                temp_mask = mask ^ (1 << j)
                if temp_mask in mask_map:
                    max_len = max(max_len, i - mask_map[temp_mask])
        
        return max_len