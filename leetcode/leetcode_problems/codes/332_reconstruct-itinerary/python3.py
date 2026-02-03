"""
Problem: Reconstruct Itinerary
Difficulty: Hard
Tags: string, graph, search

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

from collections import defaultdict

class Solution:
    def findItinerary(self, tickets: List[List[str]]) -> List[str]:
        graph = defaultdict(list)
        for src, dst in tickets:
            graph[src].append(dst)
        
        for src in graph:
            graph[src].sort(reverse=True)
        
        result = []
        
        def dfs(airport):
            while graph[airport]:
                next_airport = graph[airport].pop()
                dfs(next_airport)
            result.append(airport)
        
        dfs("JFK")
        return result[::-1]