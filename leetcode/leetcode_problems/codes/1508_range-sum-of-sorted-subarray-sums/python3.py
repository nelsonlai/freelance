"""
Problem: Range Sum of Sorted Subarray Sums
Difficulty: Medium
Tags: array, sort, search

Approach: Generate all subarray sums, sort, sum elements from left to right
Time Complexity: O(n^2 log n) for generating and sorting
Space Complexity: O(n^2) for subarray sums
"""

class Solution:
    def rangeSum(self, nums: List[int], n: int, left: int, right: int) -> int:
        MOD = 10**9 + 7
        subarray_sums = []
        
        for i in range(n):
            current_sum = 0
            for j in range(i, n):
                current_sum += nums[j]
                subarray_sums.append(current_sum)
        
        subarray_sums.sort()
        return sum(subarray_sums[left-1:right]) % MOD