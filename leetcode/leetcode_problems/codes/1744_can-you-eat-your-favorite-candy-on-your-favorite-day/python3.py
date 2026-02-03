"""
Problem: Can You Eat Your Favorite Candy on Your Favorite Day?
Difficulty: Medium
Tags: array, prefix sum

Approach: Calculate prefix sum, check if favorite day is within valid range
Time Complexity: O(n + q) where n is candies, q is queries
Space Complexity: O(n) for prefix sum
"""

class Solution:
    def canEat(self, candiesCount: List[int], queries: List[List[int]]) -> List[bool]:
        prefix = [0]
        for count in candiesCount:
            prefix.append(prefix[-1] + count)
        
        result = []
        for favoriteType, favoriteDay, dailyCap in queries:
            # Minimum candies eaten before favorite type
            min_before = prefix[favoriteType]
            # Maximum candies eaten before favorite type
            max_before = prefix[favoriteType + 1] - 1
            
            # Candies eaten by favorite day
            min_eaten = favoriteDay + 1  # At least 1 per day
            max_eaten = (favoriteDay + 1) * dailyCap  # At most dailyCap per day
            
            # Check overlap
            result.append(min_eaten <= max_before and max_eaten >= min_before)
        
        return result