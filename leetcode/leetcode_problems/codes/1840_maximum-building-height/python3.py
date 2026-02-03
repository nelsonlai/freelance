"""
Problem: Maximum Building Height
Difficulty: Hard
Tags: array, math, sort, greedy

Approach: Sort restrictions, propagate constraints left and right
Time Complexity: O(m log m) where m is restrictions
Space Complexity: O(m)
"""

class Solution:
    def maxBuilding(self, n: int, restrictions: List[List[int]]) -> int:
        restrictions.append([1, 0])
        restrictions.sort()
        
        # Propagate constraints from left to right
        for i in range(1, len(restrictions)):
            restrictions[i][1] = min(restrictions[i][1], 
                                     restrictions[i-1][1] + restrictions[i][0] - restrictions[i-1][0])
        
        # Propagate constraints from right to left
        for i in range(len(restrictions) - 2, -1, -1):
            restrictions[i][1] = min(restrictions[i][1],
                                    restrictions[i+1][1] + restrictions[i+1][0] - restrictions[i][0])
        
        result = 0
        for i in range(len(restrictions) - 1):
            left_pos, left_height = restrictions[i]
            right_pos, right_height = restrictions[i+1]
            
            # Maximum height between two restrictions
            max_height = (left_height + right_height + right_pos - left_pos) // 2
            result = max(result, max_height)
        
        return result