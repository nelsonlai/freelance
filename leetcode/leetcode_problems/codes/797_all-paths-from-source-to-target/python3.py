class Solution:
    def allPathsSourceTarget(self, graph: List[List[int]]) -> List[List[int]]:
        result = []
        
        def dfs(node, path):
            if node == len(graph) - 1:
                result.append(path[:])
                return
            
            for neighbor in graph[node]:
                path.append(neighbor)
                dfs(neighbor, path)
                path.pop()
        
        dfs(0, [0])
        return result
