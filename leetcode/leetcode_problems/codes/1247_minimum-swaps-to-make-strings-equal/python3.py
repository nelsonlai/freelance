"""
Problem: Minimum Swaps to Make Strings Equal
Difficulty: Medium
Tags: string, greedy, math

Approach: Count mismatches - (x,y) and (y,x) pairs, each pair needs 1 swap, single pairs need 2 swaps
Time Complexity: O(n) where n is length of strings
Space Complexity: O(1)
"""

class Solution:
    def minimumSwap(self, s1: str, s2: str) -> int:
        xy = yx = 0
        
        for i in range(len(s1)):
            if s1[i] == 'x' and s2[i] == 'y':
                xy += 1
            elif s1[i] == 'y' and s2[i] == 'x':
                yx += 1
        
        if (xy + yx) % 2 != 0:
            return -1
        
        return xy // 2 + yx // 2 + (xy % 2) * 2