"""
Problem: Grid Illumination
Difficulty: Hard
Tags: array, hash

Approach: Use hash maps to track illuminated rows, columns, and diagonals
Time Complexity: O(lamps + queries)
Space Complexity: O(lamps) for hash maps
"""

from collections import defaultdict

class Solution:
    def gridIllumination(self, n: int, lamps: List[List[int]], queries: List[List[int]]) -> List[int]:
        row_count = defaultdict(int)
        col_count = defaultdict(int)
        diag1_count = defaultdict(int)  # row - col
        diag2_count = defaultdict(int)  # row + col
        lamp_set = set()
        
        for r, c in lamps:
            lamp_set.add((r, c))
            row_count[r] += 1
            col_count[c] += 1
            diag1_count[r - c] += 1
            diag2_count[r + c] += 1
        
        result = []
        directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 0), (0, 1), (1, -1), (1, 0), (1, 1)]
        
        for r, c in queries:
            if row_count[r] > 0 or col_count[c] > 0 or diag1_count[r - c] > 0 or diag2_count[r + c] > 0:
                result.append(1)
            else:
                result.append(0)
            
            # Turn off lamps in 3x3 area
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if (nr, nc) in lamp_set:
                    lamp_set.remove((nr, nc))
                    row_count[nr] -= 1
                    col_count[nc] -= 1
                    diag1_count[nr - nc] -= 1
                    diag2_count[nr + nc] -= 1
        
        return result