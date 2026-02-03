"""
Problem: Find Center of Star Graph
Difficulty: Easy
Tags: array, graph

Approach: Center appears in all edges, check first two edges
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def findCenter(self, edges: List[List[int]]) -> int:
        if edges[0][0] in edges[1]:
            return edges[0][0]
        return edges[0][1]