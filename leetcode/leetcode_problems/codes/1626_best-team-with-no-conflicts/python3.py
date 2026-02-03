"""
Problem: Best Team With No Conflicts
Difficulty: Medium
Tags: array, dp, sort

Approach: Sort by age then score, DP - dp[i] = max score ending at player i
Time Complexity: O(n^2) where n is number of players
Space Complexity: O(n) for DP
"""

class Solution:
    def bestTeamScore(self, scores: List[int], ages: List[int]) -> int:
        players = sorted(zip(ages, scores))
        n = len(players)
        dp = [0] * n
        
        for i in range(n):
            dp[i] = players[i][1]
            for j in range(i):
                if players[j][1] <= players[i][1]:
                    dp[i] = max(dp[i], dp[j] + players[i][1])
        
        return max(dp)