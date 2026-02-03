"""
Problem: Maximum Length of a Concatenated String with Unique Characters
Difficulty: Medium
Tags: array, string

Approach: Backtracking - try all combinations, use bitmask to track used characters
Time Complexity: O(2^n) where n is number of strings
Space Complexity: O(n) for recursion stack
"""

class Solution:
    def maxLength(self, arr: List[str]) -> int:
        # Filter out strings with duplicate characters
        arr = [s for s in arr if len(s) == len(set(s))]
        
        def to_mask(s):
            mask = 0
            for char in s:
                bit = 1 << (ord(char) - ord('a'))
                if mask & bit:
                    return None
                mask |= bit
            return mask
        
        masks = []
        for s in arr:
            mask = to_mask(s)
            if mask is not None:
                masks.append((mask, len(s)))
        
        max_len = 0
        
        def backtrack(idx, current_mask, current_len):
            nonlocal max_len
            max_len = max(max_len, current_len)
            
            for i in range(idx, len(masks)):
                mask, length = masks[i]
                if current_mask & mask == 0:
                    backtrack(i + 1, current_mask | mask, current_len + length)
        
        backtrack(0, 0, 0)
        return max_len