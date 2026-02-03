"""
Problem: Check if One String Swap Can Make Strings Equal
Difficulty: Easy
Tags: string, hash

Approach: Find positions where characters differ, check if exactly 2 and can be swapped
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def areAlmostEqual(self, s1: str, s2: str) -> bool:
        if s1 == s2:
            return True
        
        diff = []
        for i in range(len(s1)):
            if s1[i] != s2[i]:
                diff.append(i)
        
        return len(diff) == 2 and s1[diff[0]] == s2[diff[1]] and s1[diff[1]] == s2[diff[0]]