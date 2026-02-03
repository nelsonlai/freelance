"""
Problem: Minimum Absolute Difference
Difficulty: Easy
Tags: array, sort

Approach: Sort array, find minimum difference, collect all pairs with that difference
Time Complexity: O(n log n) where n is the length of arr
Space Complexity: O(n) for result
"""

class Solution:
    def minimumAbsDifference(self, arr: List[int]) -> List[List[int]]:
        arr.sort()
        min_diff = float('inf')
        
        # Find minimum difference
        for i in range(len(arr) - 1):
            min_diff = min(min_diff, arr[i+1] - arr[i])
        
        # Collect all pairs with minimum difference
        result = []
        for i in range(len(arr) - 1):
            if arr[i+1] - arr[i] == min_diff:
                result.append([arr[i], arr[i+1]])
        
        return result