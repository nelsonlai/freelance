"""
Problem: Max Dot Product of Two Subsequences
Difficulty: Hard
Tags: array, dp

Approach: DP - dp[i][j] = max dot product using nums1[:i] and nums2[:j]
Time Complexity: O(n * m) where n, m are array lengths
Space Complexity: O(n * m) for DP table
"""

class Solution:
    def maxDotProduct(self, nums1: List[int], nums2: List[int]) -> int:
        m, n = len(nums1), len(nums2)
        dp = [[float('-inf')] * (n + 1) for _ in range(m + 1)]
        
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                product = nums1[i-1] * nums2[j-1]
                dp[i][j] = max(
                    dp[i-1][j-1] + product,
                    dp[i-1][j],
                    dp[i][j-1],
                    product
                )
        
        return dp[m][n]