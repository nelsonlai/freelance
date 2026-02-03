"""
Problem: Count Number of Special Subsequences
Difficulty: Hard
Tags: array, dp

Approach: DP - track count of subsequences ending with 0, 01, 012
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def countSpecialSubsequences(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        count0 = count01 = count012 = 0
        
        for num in nums:
            if num == 0:
                count0 = (2 * count0 + 1) % MOD
            elif num == 1:
                count01 = (2 * count01 + count0) % MOD
            else:  # num == 2
                count012 = (2 * count012 + count01) % MOD
        
        return count012