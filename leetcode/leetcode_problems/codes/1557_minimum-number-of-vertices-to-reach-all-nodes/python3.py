"""
Problem: Minimum Number of Vertices to Reach All Nodes
Difficulty: Medium
Tags: array, graph

Approach: Find nodes with no incoming edges - these must be in the set
Time Complexity: O(n + e) where n is nodes, e is edges
Space Complexity: O(n) for incoming set
"""

class Solution:
    def findSmallestSetOfVertices(self, n: int, edges: List[List[int]]) -> List[int]:
        has_incoming = set()
        for _, to in edges:
            has_incoming.add(to)
        
        return [i for i in range(n) if i not in has_incoming]