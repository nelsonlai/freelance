"""
Problem: Minimum Subsequence in Non-Increasing Order
Difficulty: Easy
Tags: array, greedy, sort

Approach: Sort descending, greedily take largest numbers until sum > remaining
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for result
"""

class Solution:
    def minSubsequence(self, nums: List[int]) -> List[int]:
        nums.sort(reverse=True)
        total = sum(nums)
        result = []
        current_sum = 0
        
        for num in nums:
            result.append(num)
            current_sum += num
            if current_sum > total - current_sum:
                break
        
        return result