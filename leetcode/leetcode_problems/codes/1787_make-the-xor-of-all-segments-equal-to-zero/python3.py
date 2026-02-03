"""
Problem: Make the XOR of All Segments Equal to Zero
Difficulty: Hard
Tags: array, dp

Approach: DP - for position i, track XOR values and minimum changes
Time Complexity: O(n * 2^10) where 2^10 is max XOR value
Space Complexity: O(k * 2^10)
"""

from collections import Counter

class Solution:
    def minChanges(self, nums: List[int], k: int) -> int:
        n = len(nums)
        # Group by position mod k
        groups = [Counter() for _ in range(k)]
        for i, num in enumerate(nums):
            groups[i % k][num] += 1
        
        # DP: dp[i][xor] = min changes to make XOR of first i groups equal to xor
        dp = {0: 0}
        
        for i in range(k):
            new_dp = {}
            # Option 1: Change all in this group
            min_changes = min(dp.values()) + len(groups[i])
            
            for xor_val, changes in dp.items():
                # Option 2: Keep some values in this group
                for num, count in groups[i].items():
                    new_xor = xor_val ^ num
                    new_changes = changes + (len(groups[i]) - count)
                    if new_xor not in new_dp or new_changes < new_dp[new_xor]:
                        new_dp[new_xor] = new_changes
            
            # Update with minimum changes option
            for xor_val in new_dp:
                new_dp[xor_val] = min(new_dp[xor_val], min_changes)
            
            dp = new_dp
        
        return dp.get(0, n)