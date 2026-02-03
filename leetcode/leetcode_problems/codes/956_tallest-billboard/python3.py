"""
Problem: Tallest Billboard
Difficulty: Hard
Tags: array, dp

Approach: DP - track maximum height difference, dp[diff] = max height of taller side
Time Complexity: O(n * sum(rods))
Space Complexity: O(sum(rods)) for DP map
"""

from collections import defaultdict

class Solution:
    def tallestBillboard(self, rods: List[int]) -> int:
        dp = {0: 0}  # diff -> max height of taller side
        
        for rod in rods:
            new_dp = defaultdict(int)
            for diff, height in dp.items():
                # Don't use this rod
                new_dp[diff] = max(new_dp[diff], height)
                
                # Add to taller side
                new_dp[diff + rod] = max(new_dp[diff + rod], height + rod)
                
                # Add to shorter side
                new_diff = abs(diff - rod)
                new_height = max(height, height - diff + rod)
                new_dp[new_diff] = max(new_dp[new_diff], new_height)
            
            dp = new_dp
        
        return dp[0]