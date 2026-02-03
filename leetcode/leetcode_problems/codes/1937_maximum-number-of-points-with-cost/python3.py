"""
Problem: Maximum Number of Points with Cost
Difficulty: Medium
Tags: array, dp

Approach: DP with optimization - track max from left and right
Time Complexity: O(m * n) where m, n are dimensions
Space Complexity: O(n)
"""

class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        m, n = len(points), len(points[0])
        dp = points[0][:]
        
        for i in range(1, m):
            # Left to right
            left = [0] * n
            left[0] = dp[0]
            for j in range(1, n):
                left[j] = max(left[j-1] - 1, dp[j])
            
            # Right to left
            right = [0] * n
            right[n-1] = dp[n-1]
            for j in range(n-2, -1, -1):
                right[j] = max(right[j+1] - 1, dp[j])
            
            # Update dp
            for j in range(n):
                dp[j] = points[i][j] + max(left[j], right[j])
        
        return max(dp)