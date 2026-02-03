"""
Problem: String Transforms Into Another String
Difficulty: Hard
Tags: string, graph, hash

Approach: Build mapping from str1 to str2, check for cycles and conflicts
Time Complexity: O(n) where n is the length of strings
Space Complexity: O(1) since at most 26 characters
"""

class Solution:
    def canConvert(self, str1: str, str2: str) -> bool:
        if str1 == str2:
            return True
        
        mapping = {}
        for c1, c2 in zip(str1, str2):
            if c1 in mapping:
                if mapping[c1] != c2:
                    return False
            else:
                mapping[c1] = c2
        
        # If all 26 characters are used in mapping, we need a temporary character
        # But if str2 uses all 26 characters, we can't have a temporary
        if len(set(str2)) == 26:
            return False
        
        return True