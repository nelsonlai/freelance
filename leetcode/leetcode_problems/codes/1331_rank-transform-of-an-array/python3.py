"""
Problem: Rank Transform of an Array
Difficulty: Easy
Tags: array, hash, sort

Approach: Sort unique values, create rank map, apply to original array
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for rank map
"""

class Solution:
    def arrayRankTransform(self, arr: List[int]) -> List[int]:
        sorted_arr = sorted(set(arr))
        rank_map = {val: rank + 1 for rank, val in enumerate(sorted_arr)}
        return [rank_map[val] for val in arr]