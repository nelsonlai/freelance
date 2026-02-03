"""
Problem: Swap For Longest Repeated Character Substring
Difficulty: Medium
Tags: array, string, tree, hash

Approach: Group consecutive same characters, try extending groups by swapping one character
Time Complexity: O(n) where n is the length of text
Space Complexity: O(n) for groups
"""

class Solution:
    def maxRepOpt1(self, text: str) -> int:
        from collections import Counter
        
        # Group consecutive characters
        groups = []
        i = 0
        while i < len(text):
            j = i
            while j < len(text) and text[j] == text[i]:
                j += 1
            groups.append((text[i], j - i))
            i = j
        
        char_count = Counter(text)
        max_len = 0
        
        # Try extending each group
        for i, (char, length) in enumerate(groups):
            # Option 1: Use all available characters of this type
            max_len = max(max_len, min(length + 1, char_count[char]) if char_count[char] > length else length)
            
            # Option 2: Merge with next group if there's one character gap
            if i + 2 < len(groups) and groups[i+1][1] == 1 and groups[i+2][0] == char:
                total = length + 1 + groups[i+2][1]
                max_len = max(max_len, min(total, char_count[char]))
        
        return max_len