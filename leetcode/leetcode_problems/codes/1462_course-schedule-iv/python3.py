"""
Problem: Course Schedule IV
Difficulty: Medium
Tags: array, graph, sort, search

Approach: Floyd-Warshall to find all reachable pairs
Time Complexity: O(n^3) where n is numCourses
Space Complexity: O(n^2) for reachable matrix
"""

class Solution:
    def checkIfPrerequisite(self, numCourses: int, prerequisites: List[List[int]], queries: List[List[int]]) -> List[bool]:
        reachable = [[False] * numCourses for _ in range(numCourses)]
        
        for u, v in prerequisites:
            reachable[u][v] = True
        
        for k in range(numCourses):
            for i in range(numCourses):
                for j in range(numCourses):
                    reachable[i][j] = reachable[i][j] or (reachable[i][k] and reachable[k][j])
        
        return [reachable[u][v] for u, v in queries]