"""
Problem: Self Crossing
Difficulty: Hard
Tags: array, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def isSelfCrossing(self, distance: List[int]) -> bool:
        if len(distance) < 4:
            return False
        
        for i in range(3, len(distance)):
            if distance[i] >= distance[i - 2] and distance[i - 1] <= distance[i - 3]:
                return True
            if i >= 4 and distance[i - 1] == distance[i - 3] and distance[i] + distance[i - 4] >= distance[i - 2]:
                return True
            if i >= 5 and distance[i - 2] >= distance[i - 4] and distance[i - 1] <= distance[i - 3] and distance[i] + distance[i - 4] >= distance[i - 2] and distance[i - 1] + distance[i - 5] >= distance[i - 3]:
                return True
        
        return False