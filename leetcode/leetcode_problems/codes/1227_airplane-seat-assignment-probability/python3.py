"""
Problem: Airplane Seat Assignment Probability
Difficulty: Medium
Tags: dp, math

Approach: Mathematical insight - probability is always 0.5 for n > 1, 1.0 for n = 1
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def nthPersonGetsNthSeat(self, n: int) -> float:
        return 1.0 if n == 1 else 0.5