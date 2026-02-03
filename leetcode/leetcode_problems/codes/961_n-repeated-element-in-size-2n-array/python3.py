"""
Problem: N-Repeated Element in Size 2N Array
Difficulty: Easy
Tags: array, hash

Approach: Use set to find duplicate element
Time Complexity: O(n)
Space Complexity: O(n) for set
"""

class Solution:
    def repeatedNTimes(self, nums: List[int]) -> int:
        seen = set()
        for num in nums:
            if num in seen:
                return num
            seen.add(num)
        return -1