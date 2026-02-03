"""
Problem: Minimum Total Space Wasted With K Resizing Operations
Difficulty: Medium
Tags: array, dp

Approach: DP - dp[i][j] = min waste using j resizes for first i elements
Time Complexity: O(n^2 * k) where n is length
Space Complexity: O(n * k)
"""

class Solution:
    def minSpaceWastedKResizing(self, nums: List[int], k: int) -> int:
        n = len(nums)
        from functools import lru_cache
        
        @lru_cache(None)
        def waste(i, j):
            if i == 0:
                return 0
            if j == 0:
                max_val = max(nums[:i])
                return max_val * i - sum(nums[:i])
            
            result = float('inf')
            max_val = 0
            total = 0
            
            for start in range(i-1, -1, -1):
                max_val = max(max_val, nums[start])
                total += nums[start]
                waste_val = max_val * (i - start) - total
                result = min(result, waste(start, j-1) + waste_val)
            
            return result
        
        return waste(n, k)