"""
Problem: Reconstruct a 2-Row Binary Matrix
Difficulty: Medium
Tags: array, greedy

Approach: Greedy - assign 2s first, then distribute remaining 1s
Time Complexity: O(n) where n is length of colsum
Space Complexity: O(n) for result
"""

class Solution:
    def reconstructMatrix(self, upper: int, lower: int, colsum: List[int]) -> List[List[int]]:
        n = len(colsum)
        result = [[0] * n, [0] * n]
        
        # First pass: assign columns with sum 2
        for i in range(n):
            if colsum[i] == 2:
                result[0][i] = 1
                result[1][i] = 1
                upper -= 1
                lower -= 1
        
        if upper < 0 or lower < 0:
            return []
        
        # Second pass: assign remaining columns with sum 1
        for i in range(n):
            if colsum[i] == 1:
                if upper > 0:
                    result[0][i] = 1
                    upper -= 1
                elif lower > 0:
                    result[1][i] = 1
                    lower -= 1
                else:
                    return []
        
        if upper != 0 or lower != 0:
            return []
        
        return result