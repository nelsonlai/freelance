"""
Problem: Number of Sub-arrays With Odd Sum
Difficulty: Medium
Tags: array, dp, math

Approach: Track prefix sum parity, count subarrays ending at each position with odd sum
Time Complexity: O(n) where n is length of arr
Space Complexity: O(1)
"""

class Solution:
    def numOfSubarrays(self, arr: List[int]) -> int:
        MOD = 10**9 + 7
        odd_count = 0
        even_count = 1
        prefix_sum = 0
        result = 0
        
        for num in arr:
            prefix_sum += num
            if prefix_sum % 2 == 1:
                result = (result + even_count) % MOD
                odd_count += 1
            else:
                result = (result + odd_count) % MOD
                even_count += 1
        
        return result