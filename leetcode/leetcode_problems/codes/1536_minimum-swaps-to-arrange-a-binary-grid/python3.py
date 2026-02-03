"""
Problem: Minimum Swaps to Arrange a Binary Grid
Difficulty: Medium
Tags: array, greedy

Approach: For each row, count trailing zeros, greedily find closest row with enough zeros
Time Complexity: O(n^2) where n is grid size
Space Complexity: O(n) for trailing zeros
"""

class Solution:
    def minSwaps(self, grid: List[List[int]]) -> int:
        n = len(grid)
        trailing_zeros = []
        
        for row in grid:
            count = 0
            for i in range(n - 1, -1, -1):
                if row[i] == 0:
                    count += 1
                else:
                    break
            trailing_zeros.append(count)
        
        swaps = 0
        for i in range(n):
            required = n - 1 - i
            if trailing_zeros[i] >= required:
                continue
            
            found = False
            for j in range(i + 1, n):
                if trailing_zeros[j] >= required:
                    found = True
                    swaps += j - i
                    trailing_zeros[i+1:j+1] = trailing_zeros[i:j]
                    trailing_zeros[i] = trailing_zeros[j]
                    break
            
            if not found:
                return -1
        
        return swaps