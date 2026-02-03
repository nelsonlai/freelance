"""
Problem: Three Consecutive Odds
Difficulty: Easy
Tags: array

Approach: Check if any three consecutive elements are all odd
Time Complexity: O(n) where n is length of arr
Space Complexity: O(1)
"""

class Solution:
    def threeConsecutiveOdds(self, arr: List[int]) -> bool:
        for i in range(len(arr) - 2):
            if arr[i] % 2 == 1 and arr[i+1] % 2 == 1 and arr[i+2] % 2 == 1:
                return True
        return False