"""
Problem: Make Array Strictly Increasing
Difficulty: Hard
Tags: array, dp, sort, search

Approach: DP with memoization - dp[i][prev] = min operations to make arr1[0..i] strictly increasing
Time Complexity: O(n * m * log m) where n is arr1 length, m is arr2 length
Space Complexity: O(n * m) for memoization
"""

class Solution:
    def makeArrayIncreasing(self, arr1: List[int], arr2: List[int]) -> int:
        arr2 = sorted(set(arr2))
        memo = {}
        
        def dp(i, prev):
            if i == len(arr1):
                return 0
            if (i, prev) in memo:
                return memo[(i, prev)]
            
            cost = float('inf')
            # Option 1: Keep arr1[i] if it's greater than prev
            if arr1[i] > prev:
                cost = min(cost, dp(i + 1, arr1[i]))
            
            # Option 2: Replace arr1[i] with element from arr2
            import bisect
            idx = bisect.bisect_right(arr2, prev)
            if idx < len(arr2):
                cost = min(cost, 1 + dp(i + 1, arr2[idx]))
            
            memo[(i, prev)] = cost
            return cost
        
        result = dp(0, float('-inf'))
        return result if result != float('inf') else -1