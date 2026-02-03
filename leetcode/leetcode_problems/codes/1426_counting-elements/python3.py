"""
Problem: Counting Elements
Difficulty: Easy
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def countElements(self, arr: List[int]) -> int:
        arr_set = set(arr)
        count = 0
        for num in arr:
            if num + 1 in arr_set:
                count += 1
        return count