"""
Problem: Two City Scheduling
Difficulty: Medium
Tags: array, greedy, sort

Approach: Sort by difference (costA - costB), send first n/2 to A, rest to B
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def twoCitySchedCost(self, costs: List[List[int]]) -> int:
        costs.sort(key=lambda x: x[0] - x[1])
        n = len(costs) // 2
        result = 0
        
        for i in range(n):
            result += costs[i][0] + costs[i + n][1]
        
        return result