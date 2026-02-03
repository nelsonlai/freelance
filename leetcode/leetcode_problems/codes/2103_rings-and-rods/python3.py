"""
Problem: Rings and Rods
Difficulty: Easy
Tags: string, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def countPoints(self, rings: str) -> int:
        rods = {}
        for i in range(0, len(rings), 2):
            color = rings[i]
            rod = rings[i + 1]
            if rod not in rods:
                rods[rod] = set()
            rods[rod].add(color)
        
        count = 0
        for colors in rods.values():
            if len(colors) == 3:
                count += 1
        return count