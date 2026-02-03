"""
Problem: Maximum Population Year
Difficulty: Easy
Tags: array, prefix sum

Approach: Use difference array to track population changes
Time Complexity: O(n) where n is logs
Space Complexity: O(1) - fixed size array
"""

class Solution:
    def maximumPopulation(self, logs: List[List[int]]) -> int:
        years = [0] * 101  # 1950 to 2050
        
        for birth, death in logs:
            years[birth - 1950] += 1
            if death - 1950 < 100:
                years[death - 1950] -= 1
        
        max_pop = 0
        max_year = 1950
        current_pop = 0
        
        for i in range(101):
            current_pop += years[i]
            if current_pop > max_pop:
                max_pop = current_pop
                max_year = 1950 + i
        
        return max_year