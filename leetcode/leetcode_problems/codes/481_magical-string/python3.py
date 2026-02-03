"""
Problem: Magical String
Difficulty: Medium
Tags: array, string

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def magicalString(self, n: int) -> int:
        if n == 0:
            return 0
        
        s = [1, 2, 2]
        i = 2
        
        while len(s) < n:
            next_num = 3 - s[-1]
            count = s[i]
            s.extend([next_num] * count)
            i += 1
        
        return s[:n].count(1)