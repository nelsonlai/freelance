"""
Problem: Kids With the Greatest Number of Candies
Difficulty: Easy
Tags: array

Approach: Find max, check if each kid can have max with extra candies
Time Complexity: O(n) where n is length of candies
Space Complexity: O(n) for result
"""

class Solution:
    def kidsWithCandies(self, candies: List[int], extraCandies: int) -> List[bool]:
        max_candies = max(candies)
        return [candy + extraCandies >= max_candies for candy in candies]