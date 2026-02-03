"""
Problem: Minimum Sideway Jumps
Difficulty: Medium
Tags: array, dp, greedy

Approach: DP - track minimum jumps needed at each position for each lane
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def minSideJumps(self, obstacles: List[int]) -> int:
        dp = [1, 0, 1]  # Jumps needed for lanes 1, 2, 3
        
        for i in range(1, len(obstacles)):
            new_dp = [float('inf')] * 3
            
            for lane in range(3):
                if obstacles[i] == lane + 1:
                    continue
                
                if obstacles[i-1] != lane + 1:
                    new_dp[lane] = min(new_dp[lane], dp[lane])
                
                for other_lane in range(3):
                    if other_lane != lane and obstacles[i-1] != other_lane + 1:
                        new_dp[lane] = min(new_dp[lane], dp[other_lane] + 1)
            
            dp = new_dp
        
        return min(dp)