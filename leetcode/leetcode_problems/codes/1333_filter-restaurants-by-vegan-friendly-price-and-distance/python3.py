"""
Problem: Filter Restaurants by Vegan-Friendly, Price and Distance
Difficulty: Medium
Tags: array, sort

Approach: Filter by criteria, sort by rating (desc) then id (desc)
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for filtered list
"""

class Solution:
    def filterRestaurants(self, restaurants: List[List[int]], veganFriendly: int, maxPrice: int, maxDistance: int) -> List[int]:
        filtered = []
        for r in restaurants:
            id, rating, vf, price, dist = r
            if (veganFriendly == 0 or vf == 1) and price <= maxPrice and dist <= maxDistance:
                filtered.append((rating, id))
        
        filtered.sort(key=lambda x: (-x[0], -x[1]))
        return [id for _, id in filtered]