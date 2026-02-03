"""
Problem: Duplicate Zeros
Difficulty: Easy
Tags: array

Approach: Two passes - count zeros, then fill from right to left
Time Complexity: O(n)
Space Complexity: O(1)
"""

class Solution:
    def duplicateZeros(self, arr: List[int]) -> None:
        zeros = arr.count(0)
        n = len(arr)
        
        for i in range(n - 1, -1, -1):
            if i + zeros < n:
                arr[i + zeros] = arr[i]
            if arr[i] == 0:
                zeros -= 1
                if i + zeros < n:
                    arr[i + zeros] = 0