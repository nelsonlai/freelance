"""
Problem: Number of Subsequences That Satisfy the Given Sum Condition
Difficulty: Medium
Tags: array, sort, search

Approach: Sort, two pointers - for each min, count valid subsequences
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for powers of 2
"""

class Solution:
    def numSubseq(self, nums: List[int], target: int) -> int:
        MOD = 10**9 + 7
        nums.sort()
        n = len(nums)
        
        # Precompute powers of 2
        power = [1] * (n + 1)
        for i in range(1, n + 1):
            power[i] = (power[i-1] * 2) % MOD
        
        result = 0
        left, right = 0, n - 1
        
        while left <= right:
            if nums[left] + nums[right] <= target:
                result = (result + power[right - left]) % MOD
                left += 1
            else:
                right -= 1
        
        return result