"""
Problem: Minimum Index Sum of Two Lists
Difficulty: Easy
Tags: array, string, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def findRestaurant(self, list1: List[str], list2: List[str]) -> List[str]:
        index_map = {restaurant: i for i, restaurant in enumerate(list1)}
        
        min_sum = float('inf')
        result = []
        
        for j, restaurant in enumerate(list2):
            if restaurant in index_map:
                index_sum = index_map[restaurant] + j
                if index_sum < min_sum:
                    min_sum = index_sum
                    result = [restaurant]
                elif index_sum == min_sum:
                    result.append(restaurant)
        
        return result