"""
Problem: Maximum Swap
Difficulty: Medium
Tags: greedy, math

Approach: Greedy algorithm with local optimal choices
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def maximumSwap(self, num: int) -> int:
        digits = list(str(num))
        last = {int(d): i for i, d in enumerate(digits)}
        
        for i, d in enumerate(digits):
            for digit in range(9, int(d), -1):
                if digit in last and last[digit] > i:
                    digits[i], digits[last[digit]] = digits[last[digit]], digits[i]
                    return int(''.join(digits))
        
        return num