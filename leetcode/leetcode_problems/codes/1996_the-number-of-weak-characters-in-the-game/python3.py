"""
Problem: The Number of Weak Characters in the Game
Difficulty: Medium
Tags: array, greedy, sort

Approach: Sort by attack descending, defense ascending, track max defense
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def numberOfWeakCharacters(self, properties: List[List[int]]) -> int:
        properties.sort(key=lambda x: (-x[0], x[1]))
        
        count = 0
        max_defense = 0
        
        for attack, defense in properties:
            if defense < max_defense:
                count += 1
            max_defense = max(max_defense, defense)
        
        return count