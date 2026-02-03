"""
Problem: Number of Ways to Wear Different Hats to Each Other
Difficulty: Hard
Tags: array, dp

Approach: DP with bitmask - dp[mask][hat] = ways to assign hats to people in mask
Time Complexity: O(n * 2^n * m) where n is people, m is hats
Space Complexity: O(2^n * m)
"""

class Solution:
    def numberWays(self, hats: List[List[int]]) -> int:
        MOD = 10**9 + 7
        n = len(hats)
        hat_to_people = [[] for _ in range(41)]
        
        for person, hat_list in enumerate(hats):
            for hat in hat_list:
                hat_to_people[hat].append(person)
        
        dp = [0] * (1 << n)
        dp[0] = 1
        
        for hat in range(1, 41):
            new_dp = dp[:]
            for person in hat_to_people[hat]:
                for mask in range(1 << n):
                    if mask & (1 << person):
                        new_dp[mask] = (new_dp[mask] + dp[mask ^ (1 << person)]) % MOD
            dp = new_dp
        
        return dp[(1 << n) - 1]