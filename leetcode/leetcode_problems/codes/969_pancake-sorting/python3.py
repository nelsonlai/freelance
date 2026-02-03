"""
Problem: Pancake Sorting
Difficulty: Medium
Tags: array, greedy, sort

Approach: Greedy - place largest unsorted element at correct position using flips
Time Complexity: O(n^2)
Space Complexity: O(1) excluding output
"""

class Solution:
    def pancakeSort(self, arr: List[int]) -> List[int]:
        result = []
        n = len(arr)
        
        for target in range(n, 0, -1):
            idx = arr.index(target)
            if idx == target - 1:
                continue
            
            if idx > 0:
                result.append(idx + 1)
                arr[:idx + 1] = arr[:idx + 1][::-1]
            
            result.append(target)
            arr[:target] = arr[:target][::-1]
        
        return result