"""
Problem: Find Positive Integer Solution for a Given Equation
Difficulty: Medium
Tags: array, math, search

Approach: Two pointers - start from (1, 1000), move based on function value
Time Complexity: O(1000) in worst case
Space Complexity: O(1) excluding result
"""

class Solution:
    def findSolution(self, customfunction: 'CustomFunction', z: int) -> List[List[int]]:
        result = []
        x, y = 1, 1000
        
        while x <= 1000 and y >= 1:
            val = customfunction.f(x, y)
            if val == z:
                result.append([x, y])
                x += 1
                y -= 1
            elif val < z:
                x += 1
            else:
                y -= 1
        
        return result