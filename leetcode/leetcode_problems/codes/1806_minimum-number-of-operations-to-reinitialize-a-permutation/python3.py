"""
Problem: Minimum Number of Operations to Reinitialize a Permutation
Difficulty: Medium
Tags: array, math, cycle detection

Approach: Find cycle length by tracking position 1
Time Complexity: O(n)
Space Complexity: O(1)
"""

class Solution:
    def reinitializePermutation(self, n: int) -> int:
        pos = 1
        operations = 0
        
        while True:
            if pos < n // 2:
                pos = 2 * pos
            else:
                pos = 2 * pos - n + 1
            operations += 1
            if pos == 1:
                break
        
        return operations