"""
Problem: Number of Ways to Split a String
Difficulty: Medium
Tags: string, math

Approach: Count 1s, if not divisible by 3 return 0, find positions for splits
Time Complexity: O(n) where n is length of s
Space Complexity: O(1)
"""

MOD = 10**9 + 7

class Solution:
    def numWays(self, s: str) -> int:
        total_ones = s.count('1')
        if total_ones % 3 != 0:
            return 0
        
        if total_ones == 0:
            n = len(s)
            return ((n - 1) * (n - 2) // 2) % MOD
        
        target = total_ones // 3
        count = 0
        first_end = 0
        second_start = 0
        
        for i, char in enumerate(s):
            if char == '1':
                count += 1
                if count == target:
                    first_end = i
                if count == target + 1:
                    second_start = i
        
        count = 0
        second_end = 0
        third_start = 0
        
        for i, char in enumerate(s):
            if char == '1':
                count += 1
                if count == 2 * target:
                    second_end = i
                if count == 2 * target + 1:
                    third_start = i
        
        return ((second_start - first_end) * (third_start - second_end)) % MOD