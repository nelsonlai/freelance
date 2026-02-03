"""
Problem: Largest Color Value in a Directed Graph
Difficulty: Hard
Tags: array, string, graph, dp, topological sort

Approach: Topological sort with DP to track max color count per path
Time Complexity: O(n + m) where n is nodes, m is edges
Space Complexity: O(n + m)
"""

from collections import defaultdict, deque

class Solution:
    def largestPathValue(self, colors: str, edges: List[List[int]]) -> int:
        n = len(colors)
        graph = defaultdict(list)
        indegree = [0] * n
        
        for u, v in edges:
            graph[u].append(v)
            indegree[v] += 1
        
        # DP: dp[node][color] = max count of color ending at node
        dp = [[0] * 26 for _ in range(n)]
        queue = deque()
        
        for i in range(n):
            if indegree[i] == 0:
                queue.append(i)
        
        processed = 0
        result = 0
        
        while queue:
            node = queue.popleft()
            processed += 1
            
            color_idx = ord(colors[node]) - ord('a')
            dp[node][color_idx] += 1
            result = max(result, dp[node][color_idx])
            
            for neighbor in graph[node]:
                for c in range(26):
                    dp[neighbor][c] = max(dp[neighbor][c], dp[node][c])
                
                indegree[neighbor] -= 1
                if indegree[neighbor] == 0:
                    queue.append(neighbor)
        
        return result if processed == n else -1