"""
Problem: Number of Burgers with No Waste of Ingredients
Difficulty: Medium
Tags: math

Approach: Solve system: 4jumbo + 2small = tomato, jumbo + small = cheese
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def numOfBurgers(self, tomatoSlices: int, cheeseSlices: int) -> List[int]:
        # 4j + 2s = tomato, j + s = cheese
        # 4j + 2(cheese - j) = tomato
        # 4j + 2cheese - 2j = tomato
        # 2j = tomato - 2cheese
        # j = (tomato - 2cheese) / 2
        # s = cheese - j
        
        jumbo = (tomatoSlices - 2 * cheeseSlices) / 2
        small = cheeseSlices - jumbo
        
        if jumbo >= 0 and small >= 0 and jumbo == int(jumbo) and small == int(small):
            return [int(jumbo), int(small)]
        return []