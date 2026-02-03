"""
Problem: The k Strongest Values in an Array
Difficulty: Medium
Tags: array, sort

Approach: Sort, find median, sort by strength (|arr[i] - median|), return top k
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for sorted array
"""

class Solution:
    def getStrongest(self, arr: List[int], k: int) -> List[int]:
        arr.sort()
        median = arr[(len(arr) - 1) // 2]
        
        arr.sort(key=lambda x: (abs(x - median), x), reverse=True)
        return arr[:k]