"""
Problem: Maximum Alternating Subarray Sum
Difficulty: Medium
Tags: array, dp

Approach: DP - track max sum ending at each position with even/odd index
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def maximumAlternatingSubarraySum(self, nums: List[int]) -> int:
        # dp[0] = max sum ending here with even index (add)
        # dp[1] = max sum ending here with odd index (subtract)
        dp_even = nums[0]
        dp_odd = float('-inf')
        result = nums[0]
        
        for i in range(1, len(nums)):
            # Current position is even index (i % 2 == 0 means even position)
            if i % 2 == 0:
                # Can continue from previous even or start new
                dp_even = max(nums[i], dp_odd + nums[i])
                # Can continue from previous odd
                dp_odd = dp_odd + nums[i] if dp_odd != float('-inf') else float('-inf')
            else:
                # Current position is odd index
                # Can continue from previous even
                new_dp_odd = dp_even - nums[i]
                # Can continue from previous odd or start new
                new_dp_even = dp_even
                dp_odd = new_dp_odd
                dp_even = new_dp_even
            
            result = max(result, dp_even, dp_odd if dp_odd != float('-inf') else float('-inf'))
        
        return result