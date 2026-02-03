"""
Problem: Knight Dialer
Difficulty: Medium
Tags: dp

Approach: Dynamic programming - track number of ways to reach each digit
Time Complexity: O(n) where n is number of hops
Space Complexity: O(1) using constant space for DP
"""

class Solution:
    def knightDialer(self, n: int) -> int:
        if n == 1:
            return 10
        
        # Moves from each digit
        moves = {
            0: [4, 6],
            1: [6, 8],
            2: [7, 9],
            3: [4, 8],
            4: [0, 3, 9],
            5: [],
            6: [0, 1, 7],
            7: [2, 6],
            8: [1, 3],
            9: [2, 4]
        }
        
        MOD = 10**9 + 7
        dp = [1] * 10
        
        for _ in range(n - 1):
            new_dp = [0] * 10
            for digit in range(10):
                for next_digit in moves[digit]:
                    new_dp[next_digit] = (new_dp[next_digit] + dp[digit]) % MOD
            dp = new_dp
        
        return sum(dp) % MOD