"""
Problem: Maximum Height by Stacking Cuboids 
Difficulty: Hard
Tags: array, dp, sort, LIS

Approach: Sort each cuboid dimensions, then sort cuboids, find longest increasing subsequence
Time Complexity: O(n^2) where n is number of cuboids
Space Complexity: O(n)
"""

class Solution:
    def maxHeight(self, cuboids: List[List[int]]) -> int:
        # Sort dimensions of each cuboid
        for cuboid in cuboids:
            cuboid.sort()
        
        # Sort cuboids
        cuboids.sort()
        
        n = len(cuboids)
        dp = [cuboids[i][2] for i in range(n)]
        
        for i in range(n):
            for j in range(i):
                if (cuboids[j][0] <= cuboids[i][0] and 
                    cuboids[j][1] <= cuboids[i][1] and 
                    cuboids[j][2] <= cuboids[i][2]):
                    dp[i] = max(dp[i], dp[j] + cuboids[i][2])
        
        return max(dp)