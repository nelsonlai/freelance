"""
Problem: Relative Sort Array
Difficulty: Easy
Tags: array, hash, sort

Approach: Use hash map to store order from arr2, sort arr1 based on order
Time Complexity: O(n log n) where n is the length of arr1
Space Complexity: O(n) for hash map and result
"""

class Solution:
    def relativeSortArray(self, arr1: List[int], arr2: List[int]) -> List[int]:
        order_map = {num: i for i, num in enumerate(arr2)}
        
        def sort_key(x):
            if x in order_map:
                return (0, order_map[x])
            return (1, x)
        
        return sorted(arr1, key=sort_key)