"""
Problem: Find the Student that Will Replace the Chalk
Difficulty: Medium
Tags: array, search, prefix sum

Approach: Use prefix sum, find position after k mod total
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def chalkReplacer(self, chalk: List[int], k: int) -> int:
        total = sum(chalk)
        k %= total
        
        for i, amount in enumerate(chalk):
            if k < amount:
                return i
            k -= amount
        
        return 0