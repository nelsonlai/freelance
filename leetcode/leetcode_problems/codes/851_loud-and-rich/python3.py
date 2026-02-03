from collections import defaultdict

class Solution:
    def loudAndRich(self, richer: List[List[int]], quiet: List[int]) -> List[int]:
        n = len(quiet)
        graph = defaultdict(list)
        for a, b in richer:
            graph[b].append(a)
        
        result = [-1] * n
        
        def dfs(node):
            if result[node] >= 0:
                return result[node]
            result[node] = node
            for neighbor in graph[node]:
                candidate = dfs(neighbor)
                if quiet[candidate] < quiet[result[node]]:
                    result[node] = candidate
            return result[node]
        
        return [dfs(i) for i in range(n)]
