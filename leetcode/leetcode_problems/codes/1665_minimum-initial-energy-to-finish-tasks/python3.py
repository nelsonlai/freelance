"""
Problem: Minimum Initial Energy to Finish Tasks
Difficulty: Hard
Tags: array, greedy, sort

Approach: Sort by (minimum - actual), process tasks with larger difference first
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def minimumEffort(self, tasks: List[List[int]]) -> int:
        tasks.sort(key=lambda x: x[1] - x[0], reverse=True)
        
        energy = 0
        result = 0
        
        for actual, minimum in tasks:
            if energy < minimum:
                result += minimum - energy
                energy = minimum
            energy -= actual
        
        return result