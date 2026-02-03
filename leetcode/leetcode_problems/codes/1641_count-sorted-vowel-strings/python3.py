"""
Problem: Count Sorted Vowel Strings
Difficulty: Medium
Tags: string, dp, math, combinatorics

Approach: DP - dp[i][j] = count of strings of length i ending with vowel j (a=0, e=1, i=2, o=3, u=4)
Time Complexity: O(n)
Space Complexity: O(1) using rolling array
"""

class Solution:
    def countVowelStrings(self, n: int) -> int:
        # dp[j] = count of strings ending with vowel j
        dp = [1] * 5
        
        for i in range(1, n):
            for j in range(1, 5):
                dp[j] += dp[j-1]
        
        return sum(dp)