"""
Problem: K-Concatenation Maximum Sum
Difficulty: Medium
Tags: array, dp

Approach: Kadane's algorithm on single array, then consider two concatenations, and full sum
Time Complexity: O(n) where n is the length of arr
Space Complexity: O(1)
"""

class Solution:
    def kConcatenationMaxSum(self, arr: List[int], k: int) -> int:
        MOD = 10**9 + 7
        
        def kadane(arr):
            max_sum = current_sum = 0
            for num in arr:
                current_sum = max(0, current_sum + num)
                max_sum = max(max_sum, current_sum)
            return max_sum
        
        # Case 1: Maximum subarray in single array
        single_max = kadane(arr)
        
        if k == 1:
            return single_max % MOD
        
        # Case 2: Maximum spanning two arrays
        double_max = kadane(arr + arr)
        
        # Case 3: If sum is positive, can use middle arrays
        total_sum = sum(arr)
        if total_sum > 0:
            # Use all arrays except maybe first and last
            middle_sum = total_sum * (k - 2) + kadane(arr[::-1] + arr)
            return max(single_max, double_max, middle_sum) % MOD
        
        return max(single_max, double_max) % MOD