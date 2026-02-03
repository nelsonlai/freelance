"""
Problem: Minimum Cost Homecoming of a Robot in a Grid
Difficulty: Medium
Tags: array, greedy

Approach: Move directly to home, sum costs of rows and columns traversed
Time Complexity: O(m + n) where m, n are grid dimensions
Space Complexity: O(1)
"""

class Solution:
    def minCost(self, startPos: List[int], homePos: List[int], rowCosts: List[int], colCosts: List[int]) -> int:
        start_row, start_col = startPos
        home_row, home_col = homePos
        
        cost = 0
        
        # Move rows
        if start_row < home_row:
            cost += sum(rowCosts[start_row + 1:home_row + 1])
        elif start_row > home_row:
            cost += sum(rowCosts[home_row:start_row])
        
        # Move columns
        if start_col < home_col:
            cost += sum(colCosts[start_col + 1:home_col + 1])
        elif start_col > home_col:
            cost += sum(colCosts[home_col:start_col])
        
        return cost