"""
Problem: Mean of Array After Removing Some Elements
Difficulty: Easy
Tags: array, sort

Approach: Sort, remove 5% from both ends, calculate mean
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def trimMean(self, arr: List[int]) -> float:
        arr.sort()
        n = len(arr)
        remove = n // 20  # 5% from each end
        
        trimmed = arr[remove:n-remove]
        return sum(trimmed) / len(trimmed)