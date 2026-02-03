"""
Problem: Previous Permutation With One Swap
Difficulty: Medium
Tags: array, graph, greedy

Approach: Find rightmost inversion, swap with largest smaller value to the right
Time Complexity: O(n)
Space Complexity: O(1)
"""

class Solution:
    def prevPermOpt1(self, arr: List[int]) -> List[int]:
        n = len(arr)
        i = n - 2
        while i >= 0 and arr[i] <= arr[i + 1]:
            i -= 1
        
        if i < 0:
            return arr
        
        j = n - 1
        while arr[j] >= arr[i] or arr[j] == arr[j - 1]:
            j -= 1
        
        arr[i], arr[j] = arr[j], arr[i]
        return arr