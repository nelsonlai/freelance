"""
Problem: Destination City
Difficulty: Easy
Tags: array, string, graph, hash

Approach: Find city that appears only as destination (not as source)
Time Complexity: O(n) where n is number of paths
Space Complexity: O(n) for sources set
"""

class Solution:
    def destCity(self, paths: List[List[str]]) -> str:
        sources = {path[0] for path in paths}
        for path in paths:
            if path[1] not in sources:
                return path[1]
        return ""