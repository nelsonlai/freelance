"""
Problem: Number of Good Ways to Split a String
Difficulty: Medium
Tags: string, dp, hash

Approach: Precompute distinct counts from left and right, count splits with equal distinct characters
Time Complexity: O(n) where n is length of s
Space Complexity: O(n) for prefix/suffix arrays
"""

class Solution:
    def numSplits(self, s: str) -> int:
        n = len(s)
        left_distinct = [0] * n
        right_distinct = [0] * n
        
        seen = set()
        for i in range(n):
            seen.add(s[i])
            left_distinct[i] = len(seen)
        
        seen = set()
        for i in range(n - 1, -1, -1):
            seen.add(s[i])
            right_distinct[i] = len(seen)
        
        count = 0
        for i in range(n - 1):
            if left_distinct[i] == right_distinct[i + 1]:
                count += 1
        
        return count