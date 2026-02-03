"""
Problem: Can Make Arithmetic Progression From Sequence
Difficulty: Easy
Tags: array, sort

Approach: Sort array, check if differences between consecutive elements are equal
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def canMakeArithmeticProgression(self, arr: List[int]) -> bool:
        arr.sort()
        diff = arr[1] - arr[0]
        for i in range(2, len(arr)):
            if arr[i] - arr[i-1] != diff:
                return False
        return True