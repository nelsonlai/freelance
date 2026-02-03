"""
Problem: Set Mismatch
Difficulty: Easy
Tags: array, hash, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def findErrorNums(self, nums: List[int]) -> List[int]:
        n = len(nums)
        expected_sum = n * (n + 1) // 2
        actual_sum = sum(nums)
        seen = set()
        duplicate = 0
        
        for num in nums:
            if num in seen:
                duplicate = num
            seen.add(num)
        
        missing = expected_sum - (actual_sum - duplicate)
        return [duplicate, missing]