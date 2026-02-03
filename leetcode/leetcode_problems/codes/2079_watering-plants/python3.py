"""
Problem: Watering Plants
Difficulty: Medium
Tags: array, simulation

Approach: Simulate watering process, track steps and water level
Time Complexity: O(n) where n is number of plants
Space Complexity: O(1)
"""

class Solution:
    def wateringPlants(self, plants: List[int], capacity: int) -> int:
        steps = 0
        current_water = capacity
        
        for i, need in enumerate(plants):
            if current_water < need:
                # Go back to river and return
                steps += 2 * i
                current_water = capacity
            
            # Water the plant
            current_water -= need
            steps += 1
        
        return steps