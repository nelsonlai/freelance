"""
Problem: Check If All 1's Are at Least Length K Places Away
Difficulty: Easy
Tags: array

Approach: Track last position of 1, check distance to current 1
Time Complexity: O(n) where n is length of nums
Space Complexity: O(1)
"""

class Solution:
    def kLengthApart(self, nums: List[int], k: int) -> bool:
        last_one = -float('inf')
        for i, num in enumerate(nums):
            if num == 1:
                if i - last_one <= k:
                    return False
                last_one = i
        return True