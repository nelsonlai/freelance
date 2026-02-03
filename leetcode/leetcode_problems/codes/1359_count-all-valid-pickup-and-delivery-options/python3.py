"""
Problem: Count All Valid Pickup and Delivery Options
Difficulty: Hard
Tags: dp, math

Approach: Mathematical - for n orders, there are (2n)! / 2^n ways
Time Complexity: O(n)
Space Complexity: O(1)
"""

class Solution:
    def countOrders(self, n: int) -> int:
        MOD = 10**9 + 7
        result = 1
        for i in range(1, n + 1):
            result = result * (2 * i - 1) * i % MOD
        return result