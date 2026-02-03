"""
Problem: Distribute Candies
Difficulty: Easy
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def distributeCandies(self, candyType: List[int]) -> int:
        unique_types = len(set(candyType))
        max_candies = len(candyType) // 2
        return min(unique_types, max_candies)