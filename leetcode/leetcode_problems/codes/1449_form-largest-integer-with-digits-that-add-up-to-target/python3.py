"""
Problem: Form Largest Integer With Digits That Add up to Target
Difficulty: Hard
Tags: array, string, dp

Approach: DP - dp[i] = largest string for cost i, try all digits
Time Complexity: O(target * 9)
Space Complexity: O(target)
"""

class Solution:
    def largestNumber(self, cost: List[int], target: int) -> str:
        dp = [""] * (target + 1)
        
        for i in range(1, target + 1):
            for digit in range(9, 0, -1):
                c = cost[digit - 1]
                if i >= c and (i == c or dp[i - c]):
                    candidate = str(digit) + dp[i - c]
                    if len(candidate) > len(dp[i]) or (len(candidate) == len(dp[i]) and candidate > dp[i]):
                        dp[i] = candidate
        
        return dp[target] if dp[target] else "0"