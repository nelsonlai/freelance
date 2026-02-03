class Solution:
    def isBipartite(self, graph: List[List[int]]) -> bool:
        n = len(graph)
        color = {}
        
        for i in range(n):
            if i not in color:
                stack = [i]
                color[i] = 0
                while stack:
                    node = stack.pop()
                    for neighbor in graph[node]:
                        if neighbor not in color:
                            color[neighbor] = color[node] ^ 1
                            stack.append(neighbor)
                        elif color[neighbor] == color[node]:
                            return False
        return True
